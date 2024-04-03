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
#include <common-trace.hpp>

namespace {

bool testOpsEq(const yactfr::ElementSequenceIteratorPosition& pos1,
               const yactfr::ElementSequenceIteratorPosition& pos2)
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

bool testOpsGt(const yactfr::ElementSequenceIteratorPosition& pos1,
               const yactfr::ElementSequenceIteratorPosition& pos2)
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

} // namespace

int main()
{
    const auto traceTypeMsUuidPair = yactfr::fromMetadataText(metadata,
                                                              metadata + std::strlen(metadata));
    MemDataSrcFactory factory {stream, sizeof stream};
    yactfr::ElementSequence seq {*traceTypeMsUuidPair.first, factory};
    auto it1 = seq.begin();
    auto it2 = seq.begin();
    yactfr::ElementSequenceIteratorPosition pos1;
    yactfr::ElementSequenceIteratorPosition pos2;

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
