/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <istream>
#include <memory>
#include <sstream>
#include <vector>
#include <cassert>
#include <array>
#include <boost/endian/conversion.hpp>
#include <boost/uuid/nil_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/optional.hpp>

#include <yactfr/io-error.hpp>
#include <yactfr/metadata/metadata-stream.hpp>
#include <yactfr/metadata/plain-text-metadata-stream.hpp>
#include <yactfr/metadata/packetized-metadata-stream.hpp>
#include <yactfr/metadata/invalid-metadata-stream.hpp>

namespace bendian = boost::endian;
namespace buuids = boost::uuids;

namespace yactfr {
namespace internal {

class MetadataStreamDecoder final
{
public:
    explicit MetadataStreamDecoder(std::istream& stream);

    bool isPacketized() const noexcept
    {
        return _isPacketized;
    }

    std::string& text() noexcept
    {
        return _text;
    }

    Size pktCount() const noexcept
    {
        return _pktCount;
    }

    int majorVersion() const noexcept
    {
        return _majorVersion;
    }

    int minorVersion() const noexcept
    {
        return _minorVersion;
    }

    ByteOrder bo() const noexcept
    {
        if (_bo == bendian::order::little) {
            return ByteOrder::LITTLE;
        } else if (_bo == bendian::order::big) {
            return ByteOrder::BIG;
        }

        std::abort();
    }

    const buuids::uuid& uuid() const noexcept
    {
        return _uuid;
    }

private:
    struct _PktHeader
    {
        std::uint32_t magic;
        std::uint8_t uuid[16];
        std::uint32_t checksum,
                      contentSize,
                      totalSize;
        std::uint8_t compressionScheme,
                     encryptionScheme,
                     checksumScheme,
                     majorVersion,
                     minorVersion;
    };

private:
    boost::optional<_PktHeader> _readPktHeader(const bool readMagic);
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
              " more bytes at this point, got only " << _stream->gcount() << ".";
        this->_throwInvalid(ss.str());
    }

    bool _streamIsBad() const
    {
        return _stream->bad() || (_stream->fail() && !_stream->eof());
    }

    /*
     * Calls `_stream->read()` and updates the current offset on
     * success. Also checks if `_stream->gcount()` is equal to `size`
     * after reading, throwing `InvalidMetadataStream` if not.
     */
    void _expect(char * const s, const std::streamsize size)
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

    /*
     * Reads `sizeof item` bytes into `item`.
     *
     * Only throws if the stream is in a bad state (which excludes
     * anything related to EOF).
     *
     * Returns whether or not the method could read `sizeof item` bytes.
     */
    template <typename T>
    bool _readItem(T& item);

    /*
     * Like _readItem(), but throws `InvalidMetadataStream` if it can't
     * read `sizeof item` bytes.
     */
    template <typename T>
    void _expectItem(T& item);

private:
    static constexpr std::uint32_t _PKT_MAGIC = 0x75d11d57;

    // only supported CTF version as of this version of yactfr
    static constexpr int _majorVersion = 1;
    static constexpr int _minorVersion = 8;

private:
    std::istream *_stream;
    std::ios_base::iostate _origStreamMask;

    /*
     * We keep a current offset for exception messages because
     * `_stream->tellg()` is not guaranteed to return a valid offset,
     * for example if it's `std::cin`.
     */
    Index _curOffset = 0;

    bool _isPacketized = false;
    std::string _text;
    Size _pktCount = 0;
    buuids::uuid _uuid;
    bendian::order _bo = bendian::order::native;
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
     * We don't want any I/O exceptions during the decoding process (we
     * check the error flags explicitly), so temporarily set the
     * exception mask of the input stream to nothing. Save the current
     * value to restore it after the decoding process.
     */
    _origStreamMask = stream.exceptions();
    stream.exceptions(std::ios_base::goodbit);

    try {
        /*
         * Let's read the first four bytes of the stream first.
         *
         * This indicates if the metadata is packetized or not. If it's
         * not, we append those four bytes as the first four characters
         * of the metadata text and read the whole stream directly.
         *
         * Otherwise, we decode each packet, except for the magic number
         * of the first packet which is already decoded.
         *
         * It's okay to require four bytes at this point: the size of a
         * valid metadata stream, plain text or packetized, cannot be
         * under four bytes.
         */
        std::array<char, sizeof(std::uint32_t)> magicBuf;

        this->_expect(magicBuf.data(), magicBuf.size());

        const auto magic = reinterpret_cast<const std::uint32_t *>(magicBuf.data());

        if (*magic == _PKT_MAGIC) {
            _bo = bendian::order::native;
            _isPacketized = true;
        } else if (bendian::endian_reverse(*magic) == _PKT_MAGIC) {
            if (bendian::order::native == bendian::order::big) {
                _bo = bendian::order::little;
            } else {
                _bo = bendian::order::big;
            }

            _isPacketized = true;
        }

        if (_isPacketized) {
            this->_readPacketized();
        } else {
            // start with those four bytes
            _text.assign(magicBuf.begin(), magicBuf.end());
            this->_readText();
        }
    } catch (...) {
        stream.exceptions(_origStreamMask);
        throw;
    }

    // TODO: should probably use some RAII to avoid repeating this
    stream.exceptions(_origStreamMask);
}

template <typename T>
bool MetadataStreamDecoder::_readItem(T& item)
{
    assert(_stream->good());
    _stream->read(reinterpret_cast<char *>(&item), sizeof item);

    if (this->_streamIsBad()) {
        throw IOError {"Cannot read metadata stream."};
    }

    if (_stream->gcount() != sizeof item) {
        assert(_stream->eof());
        return false;
    }

    if (_bo == bendian::order::little) {
        item = bendian::little_to_native(item);
    } else {
        item = bendian::big_to_native(item);
    }

    _curOffset += sizeof item;
    return true;
}

template <typename T>
void MetadataStreamDecoder::_expectItem(T& item)
{
    if (!this->_readItem(item)) {
        this->_throwEndsPrematurely(sizeof item);
    }
}

boost::optional<MetadataStreamDecoder::_PktHeader> MetadataStreamDecoder::_readPktHeader(const bool readMagic)
{
    _PktHeader header;

    /*
     * Do not assume the alignment of `_PktHeader` fields. Any of the
     * reading operations below may throw `IOError` or
     * `InvalidMetadataStream`: this must be catched by the caller.
     */
    if (readMagic) {
        if (!this->_readItem(header.magic)) {
            if (_stream->gcount() == 0) {
                // end of stream
                return boost::none;
            } else {
                this->_throwEndsPrematurely(sizeof header.magic);
            }
        }
    } else {
        header.magic = _PKT_MAGIC;
    }

    this->_expect(reinterpret_cast<char *>(&header.uuid[0]), sizeof header.uuid);

    if (this->_streamIsBad()) {
        throw IOError {"Cannot read metadata stream."};
    }

    this->_expectItem(header.checksum);
    this->_expectItem(header.contentSize);
    this->_expectItem(header.totalSize);
    this->_expectItem(header.compressionScheme);
    this->_expectItem(header.encryptionScheme);
    this->_expectItem(header.checksumScheme);
    this->_expectItem(header.majorVersion);
    this->_expectItem(header.minorVersion);
    return header;
}

void MetadataStreamDecoder::_readPacketized()
{
    std::vector<char> buf;
    bool readMagic = false;

    /*
     * We can't initialize to `_curOffset` here because at this point we
     * already read the magic number of the first packet.
     */
    decltype(_curOffset) curPktOffset = 0;

    try {
        while (true) {
            const auto header = this->_readPktHeader(readMagic);

            if (!header) {
                // end of stream
                break;
            }

            // read magic number from now on
            readMagic = true;

            const auto pktHeaderSize = (_curOffset - curPktOffset) * 8;

            if (header->totalSize % 8 != 0) {
                std::ostringstream ss;

                ss << "packet total size: " << header->totalSize <<
                      " is not a multiple of 8.";
                this->_throwInvalid(curPktOffset, ss.str());
            }

            if (header->contentSize % 8 != 0) {
                std::ostringstream ss;

                ss << "packet content size: " << header->contentSize <<
                      " is not a multiple of 8.";
                this->_throwInvalid(curPktOffset, ss.str());
            }

            if (header->contentSize < pktHeaderSize) { std::ostringstream ss;

                ss << "packet content size (" << header->contentSize <<
                      ") should be at least " << pktHeaderSize << ".";
                this->_throwInvalid(curPktOffset, ss.str());
            }

            if (header->contentSize > header->totalSize) {
                std::ostringstream ss;

                ss << "packet content size (" <<
                      static_cast<unsigned int>(header->contentSize) <<
                      ") is greater than total size (" <<
                      static_cast<unsigned int>(header->totalSize) << ").";
                this->_throwInvalid(curPktOffset, ss.str());
            }

            if (header->majorVersion != 1 || header->minorVersion != 8) {
                std::ostringstream ss;

                ss << "unknown major or minor version (" <<
                      static_cast<unsigned int>(header->majorVersion) <<
                      "." << static_cast<unsigned int>(header->minorVersion) <<
                      ": expecting 1.8).";
                this->_throwInvalid(curPktOffset, ss.str());
            }

            if (header->compressionScheme != 0) {
                std::ostringstream ss;

                ss << "unsupported compression scheme: " <<
                      static_cast<unsigned int>(header->compressionScheme) << ".";
                this->_throwInvalid(curPktOffset, ss.str());
            }

            if (header->encryptionScheme != 0) {
                std::ostringstream ss;

                ss << "unsupported encryption scheme: " <<
                      static_cast<unsigned int>(header->encryptionScheme) << ".";
                this->_throwInvalid(curPktOffset, ss.str());
            }

            if (header->checksumScheme != 0) {
                std::ostringstream ss;

                ss << "unsupported checksum scheme: " <<
                      static_cast<unsigned int>(header->checksumScheme) << ".";
                this->_throwInvalid(curPktOffset, ss.str());
            }

            if (_pktCount == 0) {
                // use the UUID of the first packet as the UUID
                std::copy(header->uuid, header->uuid + 16, _uuid.begin());
            } else {
                buuids::uuid uuid;

                std::copy(header->uuid, header->uuid + 16, uuid.begin());

                if (uuid != _uuid) {
                    std::ostringstream ss;

                    ss << "UUID mismatch: expecting " << _uuid <<
                          " (from first packet), got " << uuid << ".";
                    this->_throwInvalid(curPktOffset, ss.str());
                }
            }

            const Size totalSizeBytes = header->totalSize / 8;
            const Size contentSizeBytes = header->contentSize / 8;
            const Size pktHeaderSizeBytes = pktHeaderSize / 8;
            const Size textSizeBytes = contentSizeBytes - pktHeaderSizeBytes;

            buf.resize(textSizeBytes);
            this->_expect(buf.data(), textSizeBytes);

            if (this->_streamIsBad()) {
                throw IOError {"Cannot read metadata stream."};
            }

            const Size paddingSizeBytes = totalSizeBytes - contentSizeBytes;

            _stream->ignore(paddingSizeBytes);

            if (static_cast<Size>(_stream->gcount()) != paddingSizeBytes) {
                this->_throwEndsPrematurely(paddingSizeBytes);
            }

            if (this->_streamIsBad()) {
                throw IOError {"Cannot read metadata stream."};
            }

            _curOffset += paddingSizeBytes;
            _text.append(buf.data(), buf.size());
            ++_pktCount;
            curPktOffset = _curOffset;
        }
    } catch (const InvalidMetadataStream& exc) {
        std::ostringstream ss;

        ss << "At packet " << _pktCount << ": " << exc.what();
        throw InvalidMetadataStream {ss.str(), exc.offset()};
    } catch (const IOError& exc) {
        std::ostringstream ss;

        ss << "At packet " << _pktCount << ": " << exc.what();
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

        constexpr Size blkSize = 4096;
        const auto textOffset = _text.size();

        _text.resize(_text.size() + blkSize);
        _stream->read(&_text[textOffset], blkSize);

        if (this->_streamIsBad()) {
            throw IOError {"Cannot read metadata stream."};
        }

        _text.resize(textOffset + _stream->gcount());
    }
}

} // namespace internal

InvalidMetadataStream::InvalidMetadataStream(std::string msg, const Index offset) :
    std::runtime_error {std::move(msg)},
    _offset {offset}
{
}

std::unique_ptr<const MetadataStream> createMetadataStream(std::istream& stream)
{
    internal::MetadataStreamDecoder decoder {stream};

    if (decoder.isPacketized()) {
        return std::unique_ptr<const PacketizedMetadataStream> {new PacketizedMetadataStream {
            std::move(decoder.text()), decoder.pktCount(),
            static_cast<unsigned int>(decoder.majorVersion()),
            static_cast<unsigned int>(decoder.minorVersion()),
            decoder.bo(), decoder.uuid()
        }};
    } else {
        return std::unique_ptr<const PlainTextMetadataStream> {new PlainTextMetadataStream {
            std::move(decoder.text())
        }};
    }
}

} // namespace yactfr
