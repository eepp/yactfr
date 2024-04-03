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
#include <elem-printer.hpp>
#include <common-trace.hpp>

namespace {

constexpr auto expected =
    "P {\n"
    "PC {\n"
    "SC:0 {\n"
    "ST {\n"
    "FLUI:magic:3254525889\n"
    "PMN:3254525889\n"
    "SLA:uuid {\n"
    "FLUI:100\n"
    "FLUI:223\n"
    "FLUI:96\n"
    "FLUI:142\n"
    "FLUI:141\n"
    "FLUI:185\n"
    "FLUI:79\n"
    "FLUI:237\n"
    "FLUI:156\n"
    "FLUI:80\n"
    "FLUI:14\n"
    "FLUI:185\n"
    "FLUI:114\n"
    "FLUI:57\n"
    "FLUI:44\n"
    "FLUI:247\n"
    "MSU:64df608e-8db9-4fed-9c50-0eb972392cf7\n"
    "}\n"
    "FLUI:stream_id:221\n"
    "}\n"
    "}\n"
    "DSI:T221\n"
    "SC:1 {\n"
    "ST {\n"
    "FLUI:packet_size:584\n"
    "FLUI:content_size:552\n"
    "FLUI:custom:4562\n"
    "}\n"
    "}\n"
    "PI:T584:C552\n"
    "ER {\n"
    "SC:2 {\n"
    "ST {\n"
    "FLUI:id:17\n"
    "}\n"
    "}\n"
    "ERI:T17\n"
    "SC:5 {\n"
    "ST {\n"
    "ST:s {\n"
    "FLUI:a:2864434397\n"
    "FLUI:b:57005\n"
    "FLUI:c:255\n"
    "}\n"
    "}\n"
    "}\n"
    "}\n"
    "ER {\n"
    "SC:2 {\n"
    "ST {\n"
    "FLUI:id:17\n"
    "}\n"
    "}\n"
    "ERI:T17\n"
    "SC:5 {\n"
    "ST {\n"
    "ST:s {\n"
    "FLUI:a:303178531\n"
    "FLUI:b:17493\n"
    "FLUI:c:102\n"
    "}\n"
    "}\n"
    "}\n"
    "}\n"
    "ER {\n"
    "SC:2 {\n"
    "ST {\n"
    "FLUI:id:34\n"
    "}\n"
    "}\n"
    "ERI:T34\n"
    "SC:4 {\n"
    "ST {\n"
    "FLUI:len:3\n"
    "}\n"
    "}\n"
    "SC:5 {\n"
    "ST {\n"
    "DLA:strings {\n"
    "NTS {\n"
    "RD:6:alert$00\n"
    "}\n"
    "NTS {\n"
    "RD:5:look$00\n"
    "}\n"
    "NTS {\n"
    "RD:5:sour$00\n"
    "}\n"
    "}\n"
    "}\n"
    "}\n"
    "}\n"
    "ER {\n"
    "SC:2 {\n"
    "ST {\n"
    "FLUI:id:17\n"
    "}\n"
    "}\n"
    "ERI:T17\n"
    "SC:5 {\n"
    "ST {\n"
    "ST:s {\n"
    "FLUI:a:404295950\n"
    "FLUI:b:62019\n"
    "FLUI:c:81\n"
    "}\n"
    "}\n"
    "}\n"
    "}\n"
    "}\n"
    "}\n"
    "P {\n"
    "PC {\n"
    "SC:0 {\n"
    "ST {\n"
    "FLUI:magic:3254525889\n"
    "PMN:3254525889\n"
    "SLA:uuid {\n"
    "FLUI:100\n"
    "FLUI:223\n"
    "FLUI:96\n"
    "FLUI:142\n"
    "FLUI:141\n"
    "FLUI:185\n"
    "FLUI:79\n"
    "FLUI:237\n"
    "FLUI:156\n"
    "FLUI:80\n"
    "FLUI:14\n"
    "FLUI:185\n"
    "FLUI:114\n"
    "FLUI:57\n"
    "FLUI:44\n"
    "FLUI:247\n"
    "MSU:64df608e-8db9-4fed-9c50-0eb972392cf7\n"
    "}\n"
    "FLUI:stream_id:35\n"
    "}\n"
    "}\n"
    "DSI:T35\n"
    "SC:1 {\n"
    "ST {\n"
    "FLUI:packet_size:352\n"
    "FLUI:content_size:352\n"
    "}\n"
    "}\n"
    "PI:T352:C352\n"
    "ER {\n"
    "ERI:T0\n"
    "SC:5 {\n"
    "ST {\n"
    "NTS:a {\n"
    "RD:6:salut$00\n"
    "}\n"
    "FLUI:b:1146447479\n"
    "}\n"
    "}\n"
    "}\n"
    "ER {\n"
    "ERI:T0\n"
    "SC:5 {\n"
    "ST {\n"
    "NTS:a {\n"
    "RD:5:Cola$00\n"
    "}\n"
    "FLUI:b:1146447479\n"
    "}\n"
    "}\n"
    "}\n"
    "}\n"
    "}\n"
    "P {\n"
    "PC {\n"
    "SC:0 {\n"
    "ST {\n"
    "FLUI:magic:3254525889\n"
    "PMN:3254525889\n"
    "SLA:uuid {\n"
    "FLUI:100\n"
    "FLUI:223\n"
    "FLUI:96\n"
    "FLUI:142\n"
    "FLUI:141\n"
    "FLUI:185\n"
    "FLUI:79\n"
    "FLUI:237\n"
    "FLUI:156\n"
    "FLUI:80\n"
    "FLUI:14\n"
    "FLUI:185\n"
    "FLUI:114\n"
    "FLUI:57\n"
    "FLUI:44\n"
    "FLUI:247\n"
    "MSU:64df608e-8db9-4fed-9c50-0eb972392cf7\n"
    "}\n"
    "FLUI:stream_id:221\n"
    "}\n"
    "}\n"
    "DSI:T221\n"
    "SC:1 {\n"
    "ST {\n"
    "FLUI:packet_size:384\n"
    "FLUI:content_size:368\n"
    "FLUI:custom:65244\n"
    "}\n"
    "}\n"
    "PI:T384:C368\n"
    "ER {\n"
    "SC:2 {\n"
    "ST {\n"
    "FLUI:id:34\n"
    "}\n"
    "}\n"
    "ERI:T34\n"
    "SC:4 {\n"
    "ST {\n"
    "FLUI:len:2\n"
    "}\n"
    "}\n"
    "SC:5 {\n"
    "ST {\n"
    "DLA:strings {\n"
    "NTS {\n"
    "RD:4:dry$00\n"
    "}\n"
    "NTS {\n"
    "RD:5:thaw$00\n"
    "}\n"
    "}\n"
    "}\n"
    "}\n"
    "}\n"
    "ER {\n"
    "SC:2 {\n"
    "ST {\n"
    "FLUI:id:17\n"
    "}\n"
    "}\n"
    "ERI:T17\n"
    "SC:5 {\n"
    "ST {\n"
    "ST:s {\n"
    "FLUI:a:16909060\n"
    "FLUI:b:1286\n"
    "FLUI:c:7\n"
    "}\n"
    "}\n"
    "}\n"
    "}\n"
    "}\n"
    "}\n";

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

    while (it != seq.end()) {
        it->accept(printer);

        auto newIt = seq.begin();

        newIt = std::move(it);

        if (it != seq.end()) {
            std::cerr << "Source element sequence iterator isn't set to end of element sequence.\n";
            return 1;
        }

        it = std::move(newIt);
        ++it;

        if (newIt != seq.end()) {
            std::cerr << "Source element sequence iterator isn't set to end of element sequence.\n";
            return 1;
        }
    }

    if (ss.str() != expected) {
        std::cerr << "Expected:\n\n" << expected << "\n" <<
                     "Got:\n\n" << ss.str();
        return 1;
    }

    // move-assign end iterator
    auto endIt = seq.end();
    auto it2 = seq.begin();

    it2 = std::move(endIt);

    if (it2 != seq.end()) {
        std::cerr << "Destination element sequence iterator isn't set to end of element sequence\n";
        return 1;
    }

    if (endIt != seq.end()) {
        std::cerr << "Source element sequence iterator isn't set to end of element sequence\n";
        return 1;
    }

    return 0;
}
