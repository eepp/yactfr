/*
 * Copyright (C) 2018-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <iostream>
#include <iomanip>
#include <memory>
#include <string>
#include <fstream>
#include <boost/uuid/uuid_io.hpp>

#include <yactfr/yactfr.hpp>
#include <elem-printer.hpp>

int main(const int argc, const char * const argv[])
{
    assert(argc >= 2);

    std::string tracePath {argv[1]};
    const auto metadataStreamPath = tracePath + "/metadata";
    const auto dsPath = tracePath + "/stream";
    std::ifstream file {metadataStreamPath, std::ios::binary};
    const auto metadataStream = yactfr::createMetadataStream(file);

    file.close();

    const auto trace = yactfr::traceFromMetadataText(metadataStream->text().begin(),
                                                     metadataStream->text().end());
    yactfr::MemoryMappedFileViewFactory factory {dsPath, 4096};

    yactfr::ElementSequence seq {trace->type(), factory};
    ElemPrinter printer {std::cout};

    try {
        for (auto it = seq.begin(); it != seq.end(); ++it) {
            std::cout << std::setw(6) << it.offset() << " ";
            it->accept(printer);
        }
    } catch (const yactfr::DecodingError& ex) {
        std::cout << std::setw(6) << ex.offset() << " " << ex.reason() << std::endl;
    }

    return 0;
}
