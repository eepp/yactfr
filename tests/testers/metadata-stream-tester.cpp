/*
 * Copyright (C) 2017-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <yactfr/yactfr.hpp>
#include <boost/uuid/uuid_io.hpp>

int main(const int argc, const char * const argv[])
{
    assert(argc >= 3);

    const auto useStdin = argv[1];
    const auto path = argv[2];

    try {
        std::istream *stream;
        std::ifstream file {argv[1]};

        if (useStdin[0] == '1') {
            stream = &std::cin;
        } else {
            file.open(path, std::ios::binary | std::ios::in);
            stream = &file;
        }

        const auto metaStream = yactfr::createMetadataStream(*stream);

        std::cout << "text-size=" << metaStream->text().size() <<
                     ",has-ctf-1-signature=" << metaStream->hasCtf1Signature();

        if (const auto pktMetadataStream = dynamic_cast<const yactfr::PacketizedMetadataStream *>(metaStream.get())) {
            std::cout << ",pkt-count=" << pktMetadataStream->packetCount() <<
                         ",major-version=" << pktMetadataStream->majorVersion() <<
                         ",minor-version=" << pktMetadataStream->minorVersion() <<
                         ",bo=";

            if (pktMetadataStream->byteOrder() == yactfr::ByteOrder::Little) {
                std::cout << "le";
            } else {
                std::cout << "be";
            }

            std::cout << ",uuid=" << pktMetadataStream->uuid();
        }
    } catch (const yactfr::InvalidMetadataStream& ex) {
        std::cerr << ex.what() << std::endl;

        if (argc >= 4) {
            const auto expectedOffset = static_cast<std::uint64_t>(std::atoll(argv[3]));

            if (ex.offset() == expectedOffset) {
                return 2;
            } else {
                return 1;
            }
        }

        return 1;
    } catch (const yactfr::IOError& ex) {
        std::cerr << ex.what() << std::endl;
        return 3;
    } catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
