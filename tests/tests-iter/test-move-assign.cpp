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

static const char * const expected =
    "PB\n"
    "PCB\n"
    "SCB:0\n"
    "STB\n"
    "U:magic:3254525889\n"
    "PM:3254525889\n"
    "AB:uuid\n"
    "U:uuid:100\n"
    "U:uuid:223\n"
    "U:uuid:96\n"
    "U:uuid:142\n"
    "U:uuid:141\n"
    "U:uuid:185\n"
    "U:uuid:79\n"
    "U:uuid:237\n"
    "U:uuid:156\n"
    "U:uuid:80\n"
    "U:uuid:14\n"
    "U:uuid:185\n"
    "U:uuid:114\n"
    "U:uuid:57\n"
    "U:uuid:44\n"
    "U:uuid:247\n"
    "PU:64df608e-8db9-4fed-9c50-0eb972392cf7\n"
    "AE\n"
    "U:stream_id:221\n"
    "STE\n"
    "SCE\n"
    "DST:221\n"
    "SCB:1\n"
    "STB\n"
    "U:packet_size:584\n"
    "EPTS:584\n"
    "U:content_size:552\n"
    "EPCS:552\n"
    "U:custom:4562\n"
    "STE\n"
    "SCE\n"
    "ERB\n"
    "SCB:2\n"
    "STB\n"
    "U:id:17\n"
    "STE\n"
    "SCE\n"
    "ERT:17\n"
    "SCB:5\n"
    "STB\n"
    "STB:s\n"
    "U:a:2864434397\n"
    "U:b:57005\n"
    "U:c:255\n"
    "STE\n"
    "STE\n"
    "SCE\n"
    "ERE\n"
    "ERB\n"
    "SCB:2\n"
    "STB\n"
    "U:id:17\n"
    "STE\n"
    "SCE\n"
    "ERT:17\n"
    "SCB:5\n"
    "STB\n"
    "STB:s\n"
    "U:a:303178531\n"
    "U:b:17493\n"
    "U:c:102\n"
    "STE\n"
    "STE\n"
    "SCE\n"
    "ERE\n"
    "ERB\n"
    "SCB:2\n"
    "STB\n"
    "U:id:34\n"
    "STE\n"
    "SCE\n"
    "ERT:34\n"
    "SCB:4\n"
    "STB\n"
    "U:len:3\n"
    "STE\n"
    "SCE\n"
    "SCB:5\n"
    "STB\n"
    "SQB:strings\n"
    "STRB:strings\n"
    "SUB:6:alert\n"
    "STRE\n"
    "STRB:strings\n"
    "SUB:5:look\n"
    "STRE\n"
    "STRB:strings\n"
    "SUB:5:sour\n"
    "STRE\n"
    "SQE\n"
    "STE\n"
    "SCE\n"
    "ERE\n"
    "ERB\n"
    "SCB:2\n"
    "STB\n"
    "U:id:17\n"
    "STE\n"
    "SCE\n"
    "ERT:17\n"
    "SCB:5\n"
    "STB\n"
    "STB:s\n"
    "U:a:404295950\n"
    "U:b:62019\n"
    "U:c:81\n"
    "STE\n"
    "STE\n"
    "SCE\n"
    "ERE\n"
    "PCE\n"
    "PE\n"
    "PB\n"
    "PCB\n"
    "SCB:0\n"
    "STB\n"
    "U:magic:3254525889\n"
    "PM:3254525889\n"
    "AB:uuid\n"
    "U:uuid:100\n"
    "U:uuid:223\n"
    "U:uuid:96\n"
    "U:uuid:142\n"
    "U:uuid:141\n"
    "U:uuid:185\n"
    "U:uuid:79\n"
    "U:uuid:237\n"
    "U:uuid:156\n"
    "U:uuid:80\n"
    "U:uuid:14\n"
    "U:uuid:185\n"
    "U:uuid:114\n"
    "U:uuid:57\n"
    "U:uuid:44\n"
    "U:uuid:247\n"
    "PU:64df608e-8db9-4fed-9c50-0eb972392cf7\n"
    "AE\n"
    "U:stream_id:35\n"
    "STE\n"
    "SCE\n"
    "DST:35\n"
    "SCB:1\n"
    "STB\n"
    "U:packet_size:352\n"
    "EPTS:352\n"
    "U:content_size:352\n"
    "EPCS:352\n"
    "STE\n"
    "SCE\n"
    "ERB\n"
    "ERT:0\n"
    "SCB:5\n"
    "STB\n"
    "STRB:a\n"
    "SUB:6:salut\n"
    "STRE\n"
    "U:b:1146447479\n"
    "STE\n"
    "SCE\n"
    "ERE\n"
    "ERB\n"
    "ERT:0\n"
    "SCB:5\n"
    "STB\n"
    "STRB:a\n"
    "SUB:5:Cola\n"
    "STRE\n"
    "U:b:1146447479\n"
    "STE\n"
    "SCE\n"
    "ERE\n"
    "PCE\n"
    "PE\n"
    "PB\n"
    "PCB\n"
    "SCB:0\n"
    "STB\n"
    "U:magic:3254525889\n"
    "PM:3254525889\n"
    "AB:uuid\n"
    "U:uuid:100\n"
    "U:uuid:223\n"
    "U:uuid:96\n"
    "U:uuid:142\n"
    "U:uuid:141\n"
    "U:uuid:185\n"
    "U:uuid:79\n"
    "U:uuid:237\n"
    "U:uuid:156\n"
    "U:uuid:80\n"
    "U:uuid:14\n"
    "U:uuid:185\n"
    "U:uuid:114\n"
    "U:uuid:57\n"
    "U:uuid:44\n"
    "U:uuid:247\n"
    "PU:64df608e-8db9-4fed-9c50-0eb972392cf7\n"
    "AE\n"
    "U:stream_id:221\n"
    "STE\n"
    "SCE\n"
    "DST:221\n"
    "SCB:1\n"
    "STB\n"
    "U:packet_size:384\n"
    "EPTS:384\n"
    "U:content_size:368\n"
    "EPCS:368\n"
    "U:custom:65244\n"
    "STE\n"
    "SCE\n"
    "ERB\n"
    "SCB:2\n"
    "STB\n"
    "U:id:34\n"
    "STE\n"
    "SCE\n"
    "ERT:34\n"
    "SCB:4\n"
    "STB\n"
    "U:len:2\n"
    "STE\n"
    "SCE\n"
    "SCB:5\n"
    "STB\n"
    "SQB:strings\n"
    "STRB:strings\n"
    "SUB:4:dry\n"
    "STRE\n"
    "STRB:strings\n"
    "SUB:5:thaw\n"
    "STRE\n"
    "SQE\n"
    "STE\n"
    "SCE\n"
    "ERE\n"
    "ERB\n"
    "SCB:2\n"
    "STB\n"
    "U:id:17\n"
    "STE\n"
    "SCE\n"
    "ERT:17\n"
    "SCB:5\n"
    "STB\n"
    "STB:s\n"
    "U:a:16909060\n"
    "U:b:1286\n"
    "U:c:7\n"
    "STE\n"
    "STE\n"
    "SCE\n"
    "ERE\n"
    "PCE\n"
    "PE\n";

int main()
{
    auto traceType = yactfr::traceTypeFromMetadataText(metadata,
                                                       metadata + std::strlen(metadata));
    auto factory = std::make_shared<MemDataSourceFactory>(stream,
                                                          sizeof(stream));
    yactfr::PacketSequence seq {traceType, factory};
    std::ostringstream ss;
    ElementPrinter printer {ss, 0};
    auto it = std::begin(seq);

    while (it != std::end(seq)) {
        it->accept(printer);

        auto newIt = std::begin(seq);

        newIt = std::move(it);

        if (it != std::end(seq)) {
            std::cerr << "Source packet sequence iterator is not set to end of packet sequence.\n";
            return 1;
        }

        it = std::move(newIt);
        ++it;

        if (newIt != std::end(seq)) {
            std::cerr << "Source packet sequence iterator is not set to end of packet sequence.\n";
            return 1;
        }
    }

    if (ss.str() != expected) {
        std::cerr << "Expected:\n\n" << expected << "\n" <<
                     "Got:\n\n" << ss.str();
        return 1;
    }

    // move-assign end iterator
    auto endIt = std::end(seq);
    auto it2 = std::begin(seq);

    it2 = std::move(endIt);

    if (it2 != std::end(seq)) {
        std::cerr << "Destination packet sequence iterator is not set to end of packet sequence\n";
        return 1;
    }

    if (endIt != std::end(seq)) {
        std::cerr << "Source packet sequence iterator is not set to end of packet sequence\n";
        return 1;
    }

    return 0;
}
