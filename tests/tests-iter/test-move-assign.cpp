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

static const auto expected =
    "P {\n"
    "PC {\n"
    "SC:0 {\n"
    "ST {\n"
    "UI:magic:3254525889\n"
    "PMN:3254525889\n"
    "SA:uuid {\n"
    "UI:100\n"
    "UI:223\n"
    "UI:96\n"
    "UI:142\n"
    "UI:141\n"
    "UI:185\n"
    "UI:79\n"
    "UI:237\n"
    "UI:156\n"
    "UI:80\n"
    "UI:14\n"
    "UI:185\n"
    "UI:114\n"
    "UI:57\n"
    "UI:44\n"
    "UI:247\n"
    "TTU:64df608e-8db9-4fed-9c50-0eb972392cf7\n"
    "}\n"
    "UI:stream_id:221\n"
    "}\n"
    "}\n"
    "DSI:221\n"
    "SC:1 {\n"
    "ST {\n"
    "UI:packet_size:584\n"
    "UI:content_size:552\n"
    "UI:custom:4562\n"
    "}\n"
    "}\n"
    "PI:584:552\n"
    "ER {\n"
    "SC:2 {\n"
    "ST {\n"
    "UI:id:17\n"
    "}\n"
    "}\n"
    "ERI:17\n"
    "SC:5 {\n"
    "ST {\n"
    "ST:s {\n"
    "UI:a:2864434397\n"
    "UI:b:57005\n"
    "UI:c:255\n"
    "}\n"
    "}\n"
    "}\n"
    "}\n"
    "ER {\n"
    "SC:2 {\n"
    "ST {\n"
    "UI:id:17\n"
    "}\n"
    "}\n"
    "ERI:17\n"
    "SC:5 {\n"
    "ST {\n"
    "ST:s {\n"
    "UI:a:303178531\n"
    "UI:b:17493\n"
    "UI:c:102\n"
    "}\n"
    "}\n"
    "}\n"
    "}\n"
    "ER {\n"
    "SC:2 {\n"
    "ST {\n"
    "UI:id:34\n"
    "}\n"
    "}\n"
    "ERI:34\n"
    "SC:4 {\n"
    "ST {\n"
    "UI:len:3\n"
    "}\n"
    "}\n"
    "SC:5 {\n"
    "ST {\n"
    "DA:strings {\n"
    "STR {\n"
    "SS:6:alert\n"
    "}\n"
    "STR {\n"
    "SS:5:look\n"
    "}\n"
    "STR {\n"
    "SS:5:sour\n"
    "}\n"
    "}\n"
    "}\n"
    "}\n"
    "}\n"
    "ER {\n"
    "SC:2 {\n"
    "ST {\n"
    "UI:id:17\n"
    "}\n"
    "}\n"
    "ERI:17\n"
    "SC:5 {\n"
    "ST {\n"
    "ST:s {\n"
    "UI:a:404295950\n"
    "UI:b:62019\n"
    "UI:c:81\n"
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
    "UI:magic:3254525889\n"
    "PMN:3254525889\n"
    "SA:uuid {\n"
    "UI:100\n"
    "UI:223\n"
    "UI:96\n"
    "UI:142\n"
    "UI:141\n"
    "UI:185\n"
    "UI:79\n"
    "UI:237\n"
    "UI:156\n"
    "UI:80\n"
    "UI:14\n"
    "UI:185\n"
    "UI:114\n"
    "UI:57\n"
    "UI:44\n"
    "UI:247\n"
    "TTU:64df608e-8db9-4fed-9c50-0eb972392cf7\n"
    "}\n"
    "UI:stream_id:35\n"
    "}\n"
    "}\n"
    "DSI:35\n"
    "SC:1 {\n"
    "ST {\n"
    "UI:packet_size:352\n"
    "UI:content_size:352\n"
    "}\n"
    "}\n"
    "PI:352:352\n"
    "ER {\n"
    "ERI:0\n"
    "SC:5 {\n"
    "ST {\n"
    "STR:a {\n"
    "SS:6:salut\n"
    "}\n"
    "UI:b:1146447479\n"
    "}\n"
    "}\n"
    "}\n"
    "ER {\n"
    "ERI:0\n"
    "SC:5 {\n"
    "ST {\n"
    "STR:a {\n"
    "SS:5:Cola\n"
    "}\n"
    "UI:b:1146447479\n"
    "}\n"
    "}\n"
    "}\n"
    "}\n"
    "}\n"
    "P {\n"
    "PC {\n"
    "SC:0 {\n"
    "ST {\n"
    "UI:magic:3254525889\n"
    "PMN:3254525889\n"
    "SA:uuid {\n"
    "UI:100\n"
    "UI:223\n"
    "UI:96\n"
    "UI:142\n"
    "UI:141\n"
    "UI:185\n"
    "UI:79\n"
    "UI:237\n"
    "UI:156\n"
    "UI:80\n"
    "UI:14\n"
    "UI:185\n"
    "UI:114\n"
    "UI:57\n"
    "UI:44\n"
    "UI:247\n"
    "TTU:64df608e-8db9-4fed-9c50-0eb972392cf7\n"
    "}\n"
    "UI:stream_id:221\n"
    "}\n"
    "}\n"
    "DSI:221\n"
    "SC:1 {\n"
    "ST {\n"
    "UI:packet_size:384\n"
    "UI:content_size:368\n"
    "UI:custom:65244\n"
    "}\n"
    "}\n"
    "PI:384:368\n"
    "ER {\n"
    "SC:2 {\n"
    "ST {\n"
    "UI:id:34\n"
    "}\n"
    "}\n"
    "ERI:34\n"
    "SC:4 {\n"
    "ST {\n"
    "UI:len:2\n"
    "}\n"
    "}\n"
    "SC:5 {\n"
    "ST {\n"
    "DA:strings {\n"
    "STR {\n"
    "SS:4:dry\n"
    "}\n"
    "STR {\n"
    "SS:5:thaw\n"
    "}\n"
    "}\n"
    "}\n"
    "}\n"
    "}\n"
    "ER {\n"
    "SC:2 {\n"
    "ST {\n"
    "UI:id:17\n"
    "}\n"
    "}\n"
    "ERI:17\n"
    "SC:5 {\n"
    "ST {\n"
    "ST:s {\n"
    "UI:a:16909060\n"
    "UI:b:1286\n"
    "UI:c:7\n"
    "}\n"
    "}\n"
    "}\n"
    "}\n"
    "}\n"
    "}\n";

int main()
{
    const auto traceTypeEnvPair = yactfr::fromMetadataText(metadata,
                                                           metadata + std::strlen(metadata));
    MemDataSrcFactory factory {stream, sizeof stream};
    yactfr::ElementSequence seq {*traceTypeEnvPair.first, factory};
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
