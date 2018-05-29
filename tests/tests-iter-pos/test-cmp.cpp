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
#include <common-trace.hpp>

static bool testOpsEq(const yactfr::PacketSequenceIteratorPosition& pos1,
                      const yactfr::PacketSequenceIteratorPosition& pos2)
{
    if (pos1 != pos2) {
        return false;
    }

    if (!(pos1 == pos2)) {
        return false;
    }

    if (pos1 < pos2) {
        return false;
    }

    if (pos1 > pos2) {
        return false;
    }

    if (!(pos1 <= pos2)) {
        return false;
    }

    if (!(pos1 >= pos2)) {
        return false;
    }

    return true;
}

static bool testOpsGt(const yactfr::PacketSequenceIteratorPosition& pos1,
                      const yactfr::PacketSequenceIteratorPosition& pos2)
{
    if (pos1 == pos2) {
        return false;
    }

    if (!(pos1 != pos2)) {
        return false;
    }

    if (!(pos1 < pos2)) {
        return false;
    }

    if (!(pos1 <= pos2)) {
        return false;
    }

    if (pos1 > pos2) {
        return false;
    }

    if (pos1 >= pos2) {
        return false;
    }

    return true;
}

int main()
{
    auto traceType = yactfr::traceTypeFromMetadataText(metadata,
                                                       metadata + std::strlen(metadata));
    auto factory = std::make_shared<MemDataSourceFactory>(stream,
                                                          sizeof(stream));
    yactfr::PacketSequence seq {traceType, factory};
    auto it1 = std::begin(seq);
    auto it2 = std::begin(seq);
    yactfr::PacketSequenceIteratorPosition pos1;
    yactfr::PacketSequenceIteratorPosition pos2;

    it1.savePosition(pos1);
    it2.savePosition(pos2);

    if (!testOpsEq(pos1, pos2)) {
        return 1;
    }

    ++it2;
    it2.savePosition(pos2);

    if (!testOpsGt(pos1, pos2)) {
        return 1;
    }

    it2.seekPacket(73);
    it2.savePosition(pos2);

    if (!testOpsGt(pos1, pos2)) {
        return 1;
    }

    return 0;
}
