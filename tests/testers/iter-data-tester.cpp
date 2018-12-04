/*
 * Copyright (C) 2018 Philippe Proulx <eepp.ca>
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
#include <yactfr/memory-mapped-file-view-factory.hpp>
#include <yactfr/metadata/trace-type-from-metadata-text.hpp>
#include <yactfr/element-sequence.hpp>
#include <yactfr/element-sequence-iterator.hpp>
#include <yactfr/element.hpp>
#include <yactfr/element-visitor.hpp>

#include <element-printer.hpp>

int main(int argc, const char* argv[])
{
    assert(argc >= 2);

    std::string tracePath {argv[1]};
    const auto metadataPath = tracePath + "/metadata";
    const auto streamPath = tracePath + "/stream";
    auto file = std::ifstream {metadataPath, std::ios::binary};
    auto metadataStream = yactfr::createMetadataStream(file);

    file.close();

    auto traceType = yactfr::traceTypeFromMetadataText(std::begin(metadataStream->text()),
                                                       std::end(metadataStream->text()));
    auto factory = std::make_shared<yactfr::MemoryMappedFileViewFactory>(streamPath, 4096);

    yactfr::ElementSequence seq {traceType, factory};
    ElementPrinter printer {std::cout};

    try {
        for (auto it = std::begin(seq); it != std::end(seq); ++it) {
            std::cout << std::setw(6) << it.offset() << " ";
            it->accept(printer);
        }
    } catch (const yactfr::DecodingError& ex) {
        std::cout << std::setw(6) << ex.offset() << " " << ex.reason() << std::endl;
    }

    return 0;
}
