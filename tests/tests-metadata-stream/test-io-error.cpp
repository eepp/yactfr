/*
 * Copyright (C) 2026 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cstdint>
#include <iostream>
#include <istream>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <utility>

#include <yactfr/yactfr.hpp>

namespace {

/*
 * Stream buffer which provides the characters of some data, one at a
 * time, and throws when reading the character at the offset `failAt`.
 *
 * An input stream catches such an exception and sets its bad bit.
 */
class FailingStreamBuf final :
    public std::streambuf
{
public:
    explicit FailingStreamBuf(std::string data, const std::size_t failAt) :
        _data {std::move(data)},
        _failAt {failAt}
    {
    }

protected:
    int_type underflow() override
    {
        if (_pos >= _failAt) {
            throw std::runtime_error {"I/O error"};
        }

        if (_pos >= _data.size()) {
            return traits_type::eof();
        }

        _ch = _data[_pos];
        ++_pos;
        this->setg(&_ch, &_ch, &_ch + 1);
        return traits_type::to_int_type(_ch);
    }

private:
    std::string _data;
    std::size_t _failAt;
    std::size_t _pos = 0;
    char _ch = '\0';
};

void appendUInt32Le(std::string& str, const std::uint32_t val)
{
    for (auto i = 0U; i < 4; ++i) {
        str.push_back(static_cast<char>((val >> (i * 8)) & 0xff));
    }
}

constexpr std::size_t pktHeaderSize = 37;

// returns a little-endian metadata stream packet containing `content`
std::string pkt(const std::string& content)
{
    std::string pkt;
    const auto size = static_cast<std::uint32_t>((pktHeaderSize + content.size()) * 8);

    appendUInt32Le(pkt, 0x75d11d57);
    pkt.append(16, '\x23');
    appendUInt32Le(pkt, 0);
    appendUInt32Le(pkt, size);
    appendUInt32Le(pkt, size);
    pkt.append({'\0', '\0', '\0', '\x01', '\x08'});
    pkt += content;
    return pkt;
}

const std::string text {"/* CTF 1.8 */\n\ntrace { major = 1; minor = 8; byte_order = le; };\n"};

/*
 * Checks that createMetadataStream() throws `IOError` with the message
 * `expectedMsg` when reading `stream`.
 */
bool checkIoError(const char * const name, std::istream& stream, const std::string& expectedMsg)
{
    try {
        yactfr::createMetadataStream(stream);
    } catch (const yactfr::IOError& exc) {
        if (exc.what() != expectedMsg) {
            std::cerr << name << ": unexpected message: `" << exc.what() << "` (expecting `" <<
                         expectedMsg << "`)\n";
            return false;
        }

        return true;
    } catch (const std::exception& exc) {
        std::cerr << name << ": unexpected exception: " << exc.what() << "\n";
        return false;
    }

    std::cerr << name << ": no exception\n";
    return false;
}

bool checkIoError(const char * const name, std::string data, const std::size_t failAt,
                  const std::string& expectedMsg)
{
    FailingStreamBuf buf {std::move(data), failAt};
    std::istream stream {&buf};

    return checkIoError(name, stream, expectedMsg);
}

} // namespace

int main()
{
    static const std::string badStateMsg {"Input stream is in a bad state before decoding."};
    static const std::string cannotReadMsg {"Cannot read metadata stream."};
    auto ok = true;

    // stream already in a failing state
    {
        FailingStreamBuf buf {text, 1000};
        std::istream stream {&buf};

        stream.setstate(std::ios_base::failbit);
        ok = checkIoError("fail-bit-before", stream, badStateMsg) && ok;
    }

    {
        FailingStreamBuf buf {text, 1000};
        std::istream stream {&buf};

        stream.setstate(std::ios_base::badbit);
        ok = checkIoError("bad-bit-before", stream, badStateMsg) && ok;
    }

    // within the first four bytes (plain text or packetized)
    ok = checkIoError("first-byte", text, 0, cannotReadMsg) && ok;
    ok = checkIoError("text-magic", text, 2, cannotReadMsg) && ok;
    ok = checkIoError("pkt-magic", pkt(text), 2, cannotReadMsg) && ok;

    // plain text: within the first block and after the first block
    ok = checkIoError("text-1", text, 10, cannotReadMsg) && ok;
    ok = checkIoError("text-2", text + std::string(5000, ' '), 4500, cannotReadMsg) && ok;

    // packetized: within the UUID, within the header after the UUID, and within the content
    {
        const auto data = pkt(text);

        ok = checkIoError("pkt-header-uuid", data, 10, "At packet 0: " + cannotReadMsg) && ok;
        ok = checkIoError("pkt-header-checksum", data, 22, "At packet 0: " + cannotReadMsg) && ok;
        ok = checkIoError("pkt-content", data, pktHeaderSize + 5,
                          "At packet 0: " + cannotReadMsg) && ok;
    }

    // packetized: within the magic number of the second packet
    {
        const auto pkt1 = pkt(text);

        ok = checkIoError("pkt-2-magic", pkt1 + pkt1, pkt1.size() + 2,
                          "At packet 1: " + cannotReadMsg) && ok;
    }

    // exception mask of the caller: restored, without throwing
    {
        FailingStreamBuf buf {text, 1000};
        std::istream stream {&buf};

        stream.exceptions(std::ios_base::failbit | std::ios_base::eofbit);

        try {
            yactfr::createMetadataStream(stream);

            if (stream.exceptions() != (std::ios_base::failbit | std::ios_base::eofbit)) {
                std::cerr << "exc-mask-fail-eof: exception mask isn't restored\n";
                ok = false;
            }
        } catch (const std::exception& exc) {
            std::cerr << "exc-mask-fail-eof: unexpected exception: " << exc.what() << "\n";
            ok = false;
        }
    }

    {
        FailingStreamBuf buf {text, 10};
        std::istream stream {&buf};

        stream.exceptions(std::ios_base::badbit);
        ok = checkIoError("exc-mask-bad", stream, cannotReadMsg) && ok;

        if (stream.exceptions() != std::ios_base::badbit) {
            std::cerr << "exc-mask-bad: exception mask isn't restored\n";
            ok = false;
        }
    }

    return ok ? 0 : 1;
}
