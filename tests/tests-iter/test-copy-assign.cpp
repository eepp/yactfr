/*
 * Copyright (C) 2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <limits>
#include <cstring>
#include <sstream>
#include <iostream>
#include <vector>

#include <yactfr/yactfr.hpp>

#include <mem-data-source-factory.hpp>
#include <element-printer.hpp>
#include <common-trace.hpp>

int main()
{
    auto traceType = yactfr::traceTypeFromMetadataText(metadata,
                                                       metadata + std::strlen(metadata));
    auto factory = std::make_shared<MemDataSourceFactory>(stream,
                                                          sizeof(stream));
    yactfr::PacketSequence seq {traceType, factory};
    std::vector<std::unique_ptr<std::ostringstream>> stringStreams;
    std::vector<std::unique_ptr<ElementPrinter>> printers;

    stringStreams.push_back(std::make_unique<std::ostringstream>());
    printers.push_back(std::make_unique<ElementPrinter>(*stringStreams.back(), 0));

    std::vector<yactfr::PacketSequenceIterator> psIts {std::begin(seq)};

    while (true) {
        auto printersIt = std::begin(printers);
        auto psItsIt = std::begin(psIts);

        // print packet sequence iterator elements
        while (psItsIt != std::end(psIts)) {
            auto& psIt = *psItsIt;
            auto& printerUp = *printersIt;

            psIt->accept(*printerUp);
            ++psItsIt;
            ++printersIt;
        }

        // advance packet sequence iterators
        for (auto& psIt : psIts) {
            ++psIt;
        }

        if (psIts.front() == std::end(seq)) {
            break;
        }

        // copy last packet sequence iterator
        psIts.push_back(std::begin(seq));
        psIts.back() = *(std::end(psIts) - 2);

        // create new string stream and printer for copy
        stringStreams.push_back(std::make_unique<std::ostringstream>());
        printers.push_back(std::make_unique<ElementPrinter>(*stringStreams.back(), 0));
    }

    const auto totalStr = stringStreams.front()->str();
    auto at = totalStr.c_str();

    for (const auto& ssUp : stringStreams) {
        if (ssUp->str() != at) {
            std::cerr << "Expected:\n\n" << at << "\nGot:\n\n" << ssUp->str();
            return 1;
        }

        at = std::strchr(at, '\n');

        if (!at) {
            std::cerr << "Expecting new line at this point, didn't find any.\n";
            return 1;
        }

        ++at;
    }

    if (*at != '\0') {
        std::cerr << "Didn't reach end of first printer's string.\n";
        return 1;
    }

    // copy end iterator
    auto end = std::end(seq);
    yactfr::PacketSequenceIterator itCopy {std::begin(seq)};

    itCopy = end;

    if (itCopy != std::end(seq)) {
        std::cerr << "Invalid copy of end packet sequence iterator.\n";
        return 1;
    }

    auto begin = std::begin(seq);

    itCopy = begin;

    if (itCopy != std::begin(seq)) {
        std::cerr << "Invalid copy of beginning packet sequence iterator.\n";
        return 1;
    }

    if (itCopy->kind() != yactfr::Element::Kind::PACKET_BEGINNING) {
        std::cerr << "Invalid current element in copy of beginning packet sequence iterator.\n";
        return 1;
    }

    return 0;
}
