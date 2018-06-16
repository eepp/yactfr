/*
 * Metadata functions.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <istream>
#include <memory>
#include <sstream>
#include <vector>
#include <boost/endian/conversion.hpp>
#include <boost/uuid/nil_generator.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <yactfr/io-error.hpp>
#include <yactfr/metadata/metadata-stream.hpp>
#include <yactfr/metadata/plain-text-metadata-stream.hpp>
#include <yactfr/metadata/packetized-metadata-stream.hpp>
#include <yactfr/metadata/invalid-metadata-stream.hpp>

namespace yactfr {

namespace bendian = boost::endian;
namespace buuids = boost::uuids;

struct MetadataStreamDecoder
{
    explicit MetadataStreamDecoder(std::istream& stream);

    bool isPacketized() const noexcept
    {
        return _isPacketized;
    }

    std::string& text() noexcept
    {
        return _text;
    }

    Size packetCount() const noexcept
    {
        return _packetCount;
    }

    int majorVersion() const noexcept
    {
        return _majorVersion;
    }

    int minorVersion() const noexcept
    {
        return _minorVersion;
    }

    ByteOrder byteOrder() const noexcept
    {
        if (_byteOrder == bendian::order::little) {
            return ByteOrder::LITTLE;
        } else if (_byteOrder == bendian::order::big) {
            return ByteOrder::BIG;
        }

        abort();
    }

    const buuids::uuid& uuid() const noexcept
    {
        return _uuid;
    }

private:
    struct _PacketHeader
    {
        std::uint32_t magic;
        std::uint8_t uuid[16];
        std::uint32_t checksum,
                      contentSize,
                      packetSize;
        std::uint8_t compressionScheme,
                     encryptionScheme,
                     checksumScheme,
                     majorVersion,
                     minorVersion;
    };

private:
    _PacketHeader _readPacketHeader(const bool readMagic);
    void _readPacketized();
    void _readText();

    void _throwInvalid(const std::string& msg) const
    {
        this->_throwInvalid(_curOffset, msg);
    }

    void _throwInvalid(const Index offset, const std::string& msg) const
    {
        std::ostringstream ss;

        ss << "Invalid metadata stream: at offset " << offset << ": " << msg;

        throw InvalidMetadataStream {ss.str(), offset};
    }

    void _throwEndsPrematurely(const Size expectedSize) const
    {
        std::ostringstream ss;

        ss << "metadata stream ends prematurely: expecting " << expectedSize <<
              " more bytes at this point, got only " <<
              _stream->gcount() << ".";
        this->_throwInvalid(ss.str());
    }

    /*
     * Calls _stream->read() and updates the current offset on success.
     * Also checks if _stream->gcount() is equal to `size` after reading,
     * throwing InvalidMetadataStream otherwise.
     */
    void _read(char *s, const std::streamsize size)
    {
        _stream->read(s, size);

        if (this->_streamIsBad()) {
            // checked by the caller
            return;
        }

        if (_stream->gcount() != size) {
            this->_throwEndsPrematurely(size);
        }

        _curOffset += _stream->gcount();
    }

    bool _streamIsBad() const
    {
        return _stream->bad() || (_stream->fail() && !_stream->eof());
    }

    template <bool CheckEof, typename T>
    void _readItem(T& item);

private:
    static constexpr std::uint32_t _PACKET_MAGIC = 0x75d11d57;

private:
    std::istream *_stream;
    std::ios_base::iostate _origStreamMask;

    /*
     * We keep a current offset for exception messages because
     * _stream->tellg() is not guaranteed to return a valid offset, for
     * example if it's std::cin.
     */
    Index _curOffset = 0;

    // only supported CTF version as of this version of yactfr
    const int _majorVersion = 1;
    const int _minorVersion = 8;

    bool _isPacketized = false;
    std::string _text;
    Size _packetCount = 0;
    buuids::uuid _uuid;
    bendian::order _byteOrder = bendian::order::native;
};

MetadataStreamDecoder::MetadataStreamDecoder(std::istream& stream) :
    _stream {&stream},
    _uuid {buuids::nil_generator {}()}
{
    // fail now if the stream is already in a failing state
    if (stream.fail() || stream.bad()) {
        throw IOError {"Input stream is in a bad state before decoding."};
    }

    /*
     * We don't want any I/O exceptions during the decoding process
     * (we check the error flags explicitly), so temporarily set the
     * stream's exception mask to nothing. Save the current value to
     * restore it after the decoding process.
     */
    _origStreamMask = stream.exceptions();
    stream.exceptions(std::ios_base::goodbit);

    /*
     * Let's read the first 4 bytes of the stream first. This indicates
     * if the metadata is packetized or not. If it's not, we append
     * those 4 bytes as the first 4 characters of the metadata text
     * and read the whole stream directly. Otherwise, we decode each
     * packet, except for the first packet's magic number which is
     * already decoded.
     */
    std::array<char, sizeof(std::uint32_t)> magicBuf;

    this->_read(magicBuf.data(), magicBuf.size());

    auto magic = reinterpret_cast<const std::uint32_t *>(magicBuf.data());

    if (*magic == _PACKET_MAGIC) {
        _byteOrder = bendian::order::native;
        _isPacketized = true;
    } else if (bendian::endian_reverse(*magic) == _PACKET_MAGIC) {
        if (bendian::order::native == bendian::order::big) {
            _byteOrder = bendian::order::little;
        } else {
            _byteOrder = bendian::order::big;
        }

        _isPacketized = true;
    }

    try {
        if (_isPacketized) {
            this->_readPacketized();
        } else {
            _text.assign(std::begin(magicBuf), std::end(magicBuf));
            this->_readText();
        }
    } catch (...) {
        stream.exceptions(_origStreamMask);
        throw;
    }

    // should probably use some RAII to avoid repeating this
    stream.exceptions(_origStreamMask);
}

template <bool CheckEof, typename T>
void MetadataStreamDecoder::_readItem(T& item)
{
    assert(_stream->good());
    _stream->read(reinterpret_cast<char *>(&item), sizeof item);

    if (this->_streamIsBad()) {
        throw IOError {"Cannot read metadata stream."};
    }

    if (_stream->gcount() != sizeof item) {
        this->_throwEndsPrematurely(sizeof item);
    }

    if (CheckEof && _stream->eof()) {
        this->_throwInvalid("metadata stream ends prematurely.");
    }

    if (_byteOrder == bendian::order::little) {
        item = bendian::little_to_native(item);
    } else {
        item = bendian::big_to_native(item);
    }

    _curOffset += sizeof item;
}

MetadataStreamDecoder::_PacketHeader MetadataStreamDecoder::_readPacketHeader(const bool readMagic)
{
    _PacketHeader header;

    /*
     * Do not assume the alignment of _PacketHeader fields. Any of the
     * read operations below can throw IOError or InvalidMetadataStream:
     * this must be catched by the caller.
     */
    if (readMagic) {
        this->_readItem<true>(header.magic);
    } else {
        header.magic = _PACKET_MAGIC;
    }

    this->_read(reinterpret_cast<char *>(&header.uuid[0]), sizeof(header.uuid));

    if (this->_streamIsBad()) {
        throw IOError {"Cannot read metadata stream."};
    }

    this->_readItem<true>(header.checksum);
    this->_readItem<true>(header.contentSize);
    this->_readItem<true>(header.packetSize);
    this->_readItem<true>(header.compressionScheme);
    this->_readItem<true>(header.encryptionScheme);
    this->_readItem<true>(header.checksumScheme);
    this->_readItem<true>(header.majorVersion);

    /*
     * Do not check the end-of-file flag for the last item because the
     * packet could be empty (no content).
     */
    this->_readItem<false>(header.minorVersion);
    return header;
}

void MetadataStreamDecoder::_readPacketized()
{
    std::vector<char> buf;
    bool readMagic = false;

    /*
     * We can't initialize to _curOffset here because at this point we
     * already read the first packet's magic.
     */
    decltype(_curOffset) curPacketOffset = 0;

    try {
        while (true) {
            if (_stream->eof()) {
                break;
            }

            const auto header = this->_readPacketHeader(readMagic);

            if (!readMagic) {
                readMagic = true;
            }

            const auto packetHeaderSize = (_curOffset - curPacketOffset) * 8;

            if (header.packetSize % 8 != 0) {
                std::ostringstream ss;

                ss << "packet size: " << header.packetSize <<
                      " is not a multiple of 8.";
                this->_throwInvalid(curPacketOffset, ss.str());
            }

            if (header.contentSize % 8 != 0) {
                std::ostringstream ss;

                ss << "content size: " << header.contentSize <<
                      " is not a multiple of 8.";
                this->_throwInvalid(curPacketOffset, ss.str());
            }

            if (header.contentSize < packetHeaderSize) {
                std::ostringstream ss;

                ss << "content size (" << header.contentSize <<
                      ") should be at least " << packetHeaderSize << ".";
                this->_throwInvalid(curPacketOffset, ss.str());
            }

            if (header.contentSize > header.packetSize) {
                std::ostringstream ss;

                ss << "content size (" <<
                      static_cast<unsigned int>(header.contentSize) <<
                      ") is greater than packet size (" <<
                      static_cast<unsigned int>(header.packetSize) << ").";
                this->_throwInvalid(curPacketOffset, ss.str());
            }

            if (header.majorVersion != 1 || header.minorVersion != 8) {
                std::ostringstream ss;

                ss << "unknown major or minor version (" <<
                      static_cast<unsigned int>(header.majorVersion) <<
                      "." << static_cast<unsigned int>(header.minorVersion) <<
                      ": only 1.8 is supported).";
                this->_throwInvalid(curPacketOffset, ss.str());
            }

            if (header.compressionScheme != 0) {
                std::ostringstream ss;

                ss << "unsupported compression scheme: " <<
                      static_cast<unsigned int>(header.compressionScheme) << ".";
                this->_throwInvalid(curPacketOffset, ss.str());
            }

            if (header.encryptionScheme != 0) {
                std::ostringstream ss;

                ss << "unsupported encryption scheme: " <<
                      static_cast<unsigned int>(header.encryptionScheme) << ".";
                this->_throwInvalid(curPacketOffset, ss.str());
            }

            if (header.checksumScheme != 0) {
                std::ostringstream ss;

                ss << "unsupported checksum scheme: " <<
                      static_cast<unsigned int>(header.checksumScheme) << ".";
                this->_throwInvalid(curPacketOffset, ss.str());
            }

            if (_packetCount == 0) {
                // use the first packet's UUID as the UUID
                std::copy(header.uuid, header.uuid + 16, std::begin(_uuid));
            } else {
                buuids::uuid uuid;

                std::copy(header.uuid, header.uuid + 16, std::begin(uuid));

                if (uuid != _uuid) {
                    std::ostringstream ss;

                    ss << "UUID mismatch: expecting " << _uuid <<
                          " (from packet #0), got " << uuid << ".";
                    this->_throwInvalid(curPacketOffset, ss.str());
                }
            }

            const Size packetSizeBytes = header.packetSize / 8;
            const Size contentSizeBytes = header.contentSize / 8;
            const Size packetHeaderSizeBytes = packetHeaderSize / 8;
            const Size textSizeBytes = contentSizeBytes - packetHeaderSizeBytes;

            buf.resize(textSizeBytes);
            this->_read(buf.data(), textSizeBytes);

            if (this->_streamIsBad()) {
                throw IOError {"Cannot read metadata stream."};
            }

            const Size paddingSizeBytes = packetSizeBytes - contentSizeBytes;

            _stream->ignore(paddingSizeBytes);

            if (static_cast<decltype(paddingSizeBytes)>(_stream->gcount()) != paddingSizeBytes) {
                this->_throwEndsPrematurely(paddingSizeBytes);
            }

            if (this->_streamIsBad()) {
                throw IOError {"Cannot read metadata stream."};
            }

            _curOffset += paddingSizeBytes;
            _text.append(buf.data(), buf.size());
            ++_packetCount;
            curPacketOffset = _curOffset;
        }
    } catch (const InvalidMetadataStream &ex) {
        std::ostringstream ss;

        ss << "At packet " << _packetCount << ": " << ex.what();
        throw InvalidMetadataStream {ss.str(), ex.offset()};
    } catch (const IOError& ex) {
        std::ostringstream ss;

        ss << "At packet " << _packetCount << ": " << ex.what();
        throw IOError {ss.str()};
    }
}

void MetadataStreamDecoder::_readText()
{
    // just read everything
    while (true) {
        if (_stream->eof()) {
            break;
        }

        static const Size blockSize = 4096;
        const auto textOffset = _text.size();

        _text.resize(_text.size() + blockSize);
        _stream->read(&_text[textOffset], blockSize);

        if (this->_streamIsBad()) {
            throw IOError {"Cannot read metadata stream."};
        }

        _text.resize(textOffset + _stream->gcount());
    }
}

InvalidMetadataStream::InvalidMetadataStream(const std::string& msg, const Index offset) :
    std::runtime_error {msg},
    _offset {offset}
{
}

std::unique_ptr<const MetadataStream> createMetadataStream(std::istream& stream)
{
    MetadataStreamDecoder decoder {stream};
    MetadataStream *metadataStream;

    if (decoder.isPacketized()) {
        metadataStream = new PacketizedMetadataStream {
            std::move(decoder.text()), decoder.packetCount(),
            static_cast<unsigned int>(decoder.majorVersion()),
            static_cast<unsigned int>(decoder.minorVersion()),
            decoder.byteOrder(), decoder.uuid()
        };
    } else {
        metadataStream = new PlainTextMetadataStream {std::move(decoder.text())};
    }

    return std::unique_ptr<const MetadataStream> {metadataStream};
}

} // namespace yactfr
