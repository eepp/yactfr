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
#include <common-trace.hpp>

int main()
{
    const auto traceTypeEnvPair = yactfr::fromMetadataText(metadata,
                                                           metadata + std::strlen(metadata));
    MemDataSrcFactory factory {stream, sizeof stream};
    yactfr::ElementSequence seq {*traceTypeEnvPair.first, factory};
    const auto it = seq.begin();

    yactfr::ElementSequenceIteratorPosition pos;

    if (pos) {
        std::cerr << "Position is true.\n";
        return 1;
    }

    it.savePosition(pos);

    if (!pos) {
        std::cerr << "Position is false.\n";
        return 1;
    }

    return 0;
}
