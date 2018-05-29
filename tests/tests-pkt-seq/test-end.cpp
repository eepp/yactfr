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
    std::ostringstream ss;
    auto it = std::end(seq);

    // this test is pretty much useless lel
    if (it != std::end(seq)) {
        return 1;
    }

    return 0;
}
