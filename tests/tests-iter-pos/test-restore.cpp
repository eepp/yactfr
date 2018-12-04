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
#include <iterator>
#include <vector>

#include <yactfr/yactfr.hpp>

#include <mem-data-source-factory.hpp>
#include <element-printer.hpp>
#include <common-trace.hpp>

static const char * const expected =
    "U:uuid:142\n"
    "PM:3254525889\n";

int main()
{
    auto traceType = yactfr::traceTypeFromMetadataText(metadata,
                                                       metadata + std::strlen(metadata));
    auto factory = std::make_shared<MemDataSourceFactory>(stream,
                                                          sizeof(stream));
    yactfr::ElementSequence seq {traceType, factory};
    std::ostringstream ss;
    ElementPrinter printer {ss, 0};
    auto it = std::begin(seq);

    std::advance(it, 5);

    yactfr::ElementSequenceIteratorPosition pos;

    it.savePosition(pos);
    std::advance(it, 5);
    it->accept(printer);
    it.restorePosition(pos);
    it->accept(printer);

    if (ss.str() != expected) {
        std::cerr << "Expected:\n\n" << expected << "\n" <<
                     "Got:\n\n" << ss.str();
        return 1;
    }

    // restore an "end" iterator
    it = std::begin(seq);
    std::advance(it, 5);
    it.savePosition(pos);
    std::advance(it, 5);
    ss.str(std::string {});
    it->accept(printer);

    auto it2 = std::end(seq);

    it2.restorePosition(pos);
    it2->accept(printer);

    if (ss.str() != expected) {
        std::cerr << "Expected:\n\n" << expected << "\n" <<
                     "Got:\n\n" << ss.str();
        return 1;
    }

    // restore an iterator which was moved and reset
    it = std::begin(seq);
    std::advance(it, 5);
    it.savePosition(pos);
    std::advance(it, 5);
    ss.str(std::string {});
    it->accept(printer);
    it2 = std::move(it);
    ++it2;
    it.restorePosition(pos);
    it->accept(printer);

    if (ss.str() != expected) {
        std::cerr << "Expected:\n\n" << expected << "\n" <<
                     "Got:\n\n" << ss.str();
        return 1;
    }

    return 0;
}
