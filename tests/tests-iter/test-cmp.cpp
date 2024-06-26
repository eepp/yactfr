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

bool testOpsEq(const yactfr::ElementSequenceIterator& it1,
               const yactfr::ElementSequenceIterator& it2)
{
    if (it1 != it2) {
        return false;
    }

    if (!(it1 == it2)) {
        return false;
    }

    if (it1 < it2) {
        return false;
    }

    if (it1 > it2) {
        return false;
    }

    if (!(it1 <= it2)) {
        return false;
    }

    if (!(it1 >= it2)) {
        return false;
    }

    return true;
}

bool testOpsGt(const yactfr::ElementSequenceIterator& it1,
               const yactfr::ElementSequenceIterator& it2)
{
    if (it1 == it2) {
        return false;
    }

    if (!(it1 != it2)) {
        return false;
    }

    if (!(it1 < it2)) {
        return false;
    }

    if (!(it1 <= it2)) {
        return false;
    }

    if (it1 > it2) {
        return false;
    }

    if (it1 >= it2) {
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

    if (!testOpsEq(it1, it2)) {
        return 1;
    }

    ++it2;

    if (!testOpsGt(it1, it2)) {
        return 1;
    }

    it2.seekPacket(73);

    if (!testOpsGt(it1, it2)) {
        return 1;
    }

    it2 = it1;
    it1 = seq.end();

    if (!testOpsGt(it2, it1)) {
        return 1;
    }

    it2 = seq.end();

    if (!testOpsEq(it1, it2)) {
        return 1;
    }

    return 0;
}
