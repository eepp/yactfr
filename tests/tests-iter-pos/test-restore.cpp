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
#include <iterator>
#include <vector>

#include <yactfr/yactfr.hpp>

#include <mem-data-src-factory.hpp>
#include <elem-printer.hpp>
#include <common-trace.hpp>

namespace {

constexpr auto expected =
    "FLUI:142\n"
    "PMN:3254525889\n";

} // namespace

int main()
{
    const auto traceTypeMsUuidPair = yactfr::fromMetadataText(metadata,
                                                              metadata + std::strlen(metadata));
    MemDataSrcFactory factory {stream, sizeof stream};
    yactfr::ElementSequence seq {*traceTypeMsUuidPair.first, factory};
    std::ostringstream ss;
    ElemPrinter printer {ss, 0};
    auto it = seq.begin();

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
    it = seq.begin();
    std::advance(it, 5);
    it.savePosition(pos);
    std::advance(it, 5);
    ss.str(std::string {});
    it->accept(printer);

    auto it2 = seq.end();

    it2.restorePosition(pos);
    it2->accept(printer);

    if (ss.str() != expected) {
        std::cerr << "Expected:\n\n" << expected << "\n" <<
                     "Got:\n\n" << ss.str();
        return 1;
    }

    // restore an iterator which was moved and reset
    it = seq.begin();
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
