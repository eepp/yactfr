/*
 * Copyright (C) 2018-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <memory>
#include <string>
#include <fstream>
#include <vector>
#include <boost/uuid/uuid_io.hpp>

#include <yactfr/yactfr.hpp>
#include <elem-printer.hpp>
#include <mem-data-src-factory.hpp>

/*
 * Calls `func` until it doesn't throw `yactfr::DataNotAvailable`.
 */
template <typename FuncT>
static void retryIfDataNotAvail(FuncT&& func)
{
    while (true) {
        try {
            func();
            return;
        } catch (const yactfr::DataNotAvailable&) {
            // just try again
        }
    }
}

static void printElems(const yactfr::TraceType& traceType,
                       yactfr::DataSourceFactory& factory)
{
    yactfr::ElementSequence seq {traceType, factory};
    ElemPrinter printer {std::cout};

    try {
        yactfr::ElementSequenceIterator it = seq.end();

        retryIfDataNotAvail([&seq, &it] {
            it = seq.begin();
        });

        while (it != seq.end()) {
            std::cout << std::setw(6) << it.offset() << " ";
            it->accept(printer);
            retryIfDataNotAvail([&it] {
                ++it;
            });
        }
    } catch (const yactfr::DecodingError& ex) {
        std::cout << std::setw(6) << ex.offset() << " " << ex.reason() << std::endl;
    }
}

/*
 * Usage:
 *
 *     iter-data-tester TRACE-DIR [MAX-DATA-BLOCK-SIZE [data-not-avail]]
 *
 * Without `MAX-DATA-BLOCK-SIZE`, reads the data stream file with a
 * memory-mapped file view factory.
 *
 * With `MAX-DATA-BLOCK-SIZE`, reads the data stream file from memory,
 * the data source returning data blocks of at most
 * `MAX-DATA-BLOCK-SIZE` bytes.
 *
 * With `data-not-avail`, the data source also throws
 * `yactfr::DataNotAvailable` every other time.
 */
int main(const int argc, const char * const argv[])
{
    assert(argc >= 2);

    std::string tracePath {argv[1]};
    const auto metadataStreamPath = tracePath + "/metadata";
    const auto dsPath = tracePath + "/stream";
    std::ifstream file {metadataStreamPath, std::ios::binary};
    const auto metadataStream = yactfr::createMetadataStream(file);

    file.close();

    const auto traceTypeMsUuidPair = yactfr::fromMetadataText(metadataStream->text());

    if (argc >= 3) {
        std::ifstream dsFile {dsPath, std::ios::binary};
        const std::vector<std::uint8_t> data {std::istreambuf_iterator {dsFile}, {}};
        MemDataSrcFactory factory {
            data.data(), data.size(), std::strtoull(argv[2], nullptr, 10),
            argc >= 4 && std::strcmp(argv[3], "data-not-avail") == 0
        };

        printElems(*traceTypeMsUuidPair.first, factory);
    } else {
        yactfr::MemoryMappedFileViewFactory factory {dsPath, 4096};

        printElems(*traceTypeMsUuidPair.first, factory);
    }

    return 0;
}
