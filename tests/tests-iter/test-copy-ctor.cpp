/*
 * Copyright (C) 2018-2022 Philippe Proulx <eepp.ca>
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

#include <mem-data-src-factory.hpp>
#include <elem-printer.hpp>
#include <common-trace.hpp>

int main()
{
    const auto traceTypeMsUuidPair = yactfr::fromMetadataText(metadata,
                                                              metadata + std::strlen(metadata));
    MemDataSrcFactory factory {stream, sizeof stream};
    yactfr::ElementSequence seq {*traceTypeMsUuidPair.first, factory};
    std::vector<std::unique_ptr<std::ostringstream>> stringStreams;
    std::vector<std::unique_ptr<ElemPrinter>> printers;

    stringStreams.push_back(std::make_unique<std::ostringstream>());
    printers.push_back(std::make_unique<ElemPrinter>(*stringStreams.back(), 0));

    std::vector<yactfr::ElementSequenceIterator> esIts {seq.begin()};

    while (true) {
        auto printersIt = printers.begin();
        auto esItsIt = esIts.begin();

        // print element sequence iterator elements
        while (esItsIt != esIts.end()) {
            auto& esIt = *esItsIt;
            auto& printer = *printersIt;

            esIt->accept(*printer);
            ++esItsIt;
            ++printersIt;
        }

        // advance element sequence iterators
        for (auto& esIt : esIts) {
            ++esIt;
        }

        if (esIts.front() == seq.end()) {
            break;
        }

        // copy last element sequence iterator
        yactfr::ElementSequenceIterator esItCopy {esIts.back()};

        // this actually calls yactfr::ElementSequenceIterator::operator=() too
        esIts.push_back(esItCopy);

        // create new string stream and printer for copy
        stringStreams.push_back(std::make_unique<std::ostringstream>());
        printers.push_back(std::make_unique<ElemPrinter>(*stringStreams.back(), 0));
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
        std::cerr << "Didn't reach end of first string of printer.\n";
        return 1;
    }

    // copy end iterator
    const auto end = seq.end();
    const yactfr::ElementSequenceIterator itCopy {end};

    if (itCopy != seq.end()) {
        std::cerr << "Invalid copy of end element sequence iterator.\n";
        return 1;
    }

    return 0;
}
