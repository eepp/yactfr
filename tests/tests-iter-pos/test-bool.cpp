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
#include <common-trace.hpp>

int main()
{
    auto traceType = yactfr::traceTypeFromMetadataText(metadata,
                                                       metadata + std::strlen(metadata));
    auto factory = std::make_shared<MemDataSourceFactory>(stream,
                                                          sizeof(stream));
    yactfr::PacketSequence seq {traceType, factory};
    auto it = std::begin(seq);

    yactfr::PacketSequenceIteratorPosition pos;

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
