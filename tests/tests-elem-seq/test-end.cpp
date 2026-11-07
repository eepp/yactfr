/*
 * SPDX-FileCopyrightText: 2018-2022 Philippe Proulx <eepp.ca>
 * SPDX-License-Identifier: MIT
 */

#include <sstream>

#include <yactfr/yactfr.hpp>

#include <mem-data-src-factory.hpp>
#include <common-trace.hpp>

int main()
{
    const auto traceTypeMsUuidPair = yactfr::fromMetadataText(metadata);
    MemDataSrcFactory factory {stream, sizeof stream};
    yactfr::ElementSequence seq {*traceTypeMsUuidPair.first, factory};
    std::ostringstream ss;
    const auto it = seq.end();

    // this test is pretty much useless lel
    if (it != seq.end()) {
        return 1;
    }

    return 0;
}
