/*
 * SPDX-FileCopyrightText: 2018-2022 Philippe Proulx <eepp.ca>
 * SPDX-License-Identifier: MIT
 */

#include <sstream>
#include <iostream>

#include <yactfr/yactfr.hpp>

#include <mem-data-src-factory.hpp>
#include <elem-printer.hpp>
#include <common-trace.hpp>

namespace {

constexpr auto expected = "P {\n";

} // namespace

int main()
{
    const auto traceTypeMsUuidPair = yactfr::fromMetadataText(metadata);
    MemDataSrcFactory factory {stream, sizeof stream};
    yactfr::ElementSequence seq {*traceTypeMsUuidPair.first, factory};
    std::ostringstream ss;
    ElemPrinter printer {ss, 0};
    const auto it = seq.begin();

    it->accept(printer);

    if (ss.str() != expected) {
        std::cerr << "Expected:\n\n" << expected << "\n" <<
                     "Got:\n\n" << ss.str();
        return 1;
    }

    return 0;
}
