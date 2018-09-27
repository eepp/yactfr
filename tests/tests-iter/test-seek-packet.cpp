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

#include <yactfr/yactfr.hpp>

#include <mem-data-source-factory.hpp>
#include <element-printer.hpp>

static const char * const metadata =
    "/* CTF 1.8 */\n"
    "typealias integer { size = 8; } := u8;"
    "typealias integer { size = 16; } := u16;"
    "typealias integer { size = 32; } := u32;"
    "typealias integer { size = 64; } := u64;"
    "trace {"
    "  major = 1;"
    "  minor = 8;"
    "  byte_order = be;"
    "  uuid = \"64df608e-8db9-4fed-9c50-0eb972392cf7\";"
    "  packet.header := struct {"
    "    u32 magic;"
    "    u8 uuid[16];"
    "    u8 stream_id;"
    "  };"
    "};"
    "stream {"
    "  id = 0x23;"
    "  packet.context := struct {"
    "    u16 packet_size;"
    "    u16 content_size;"
    "  };"
    "};"
    "event {"
    "  stream_id = 0x23;"
    "  fields := struct {"
    "    string a;"
    "    u32 b;"
    "  };"
    "};"
    "stream {"
    "  id = 0xdd;"
    "  packet.context := struct {"
    "    u16 packet_size;"
    "    u16 content_size;"
    "    u16 custom;"
    "  };"
    "};"
    "event {"
    "  stream_id = 0xdd;"
    "  fields := struct {"
    "    struct {"
    "      u32 a;"
    "      u16 b;"
    "      u8 c;"
    "    } s;"
    "  };"
    "};";

static const std::uint8_t stream[] = {
    // packet header
    0xc1, 0xfc, 0x1f, 0xc1,
    0x64, 0xdf, 0x60, 0x8e, 0x8d, 0xb9, 0x4f, 0xed,
    0x9c, 0x50, 0x0e, 0xb9, 0x72, 0x39, 0x2c, 0xf7,
    0xdd,

    // packet context
    0x01, 0xa0, 0x01, 0x80, 0x11, 0xd2,

    // event
    0xaa, 0xbb, 0xcc, 0xdd, 0xde, 0xad, 0xff,

    // event
    0x12, 0x12, 0x23, 0x23, 0x44, 0x55, 0x66,

    // event
    0x18, 0x19, 0x11, 0x0e, 0xf2, 0x43, 0x51,

    // padding
    0xff, 0x00, 0xf0, 0x0f,

    // packet header
    0xc1, 0xfc, 0x1f, 0xc1,
    0x64, 0xdf, 0x60, 0x8e, 0x8d, 0xb9, 0x4f, 0xed,
    0x9c, 0x50, 0x0e, 0xb9, 0x72, 0x39, 0x2c, 0xf7,
    0x23,

    // packet context
    0x01, 0x60, 0x01, 0x60,

    // event
    's', 'a', 'l', 'u', 't', 0, 0x44, 0x55, 0x66, 0x77,

    // event
    'C', 'o', 'l', 'a', 0, 0x44, 0x55, 0x66, 0x77,

    // packet header
    0xc1, 0xfc, 0x1f, 0xc1,
    0x64, 0xdf, 0x60, 0x8e, 0x8d, 0xb9, 0x4f, 0xed,
    0x9c, 0x50, 0x0e, 0xb9, 0x72, 0x39, 0x2c, 0xf7,
    0xdd,

    // packet context
    0x01, 0x20, 0x01, 0x10, 0xfe, 0xdc,

    // event
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,

    // padding
    0x11, 0x22,
};

static const char * const expected =
    "PB\n"
    "PCB\n"
    "SCB:0\n"
    "STB\n"
    "U:magic:3254525889\n"
    "PM:3254525889\n"
    "SAB:uuid\n"
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
    "PB\n"
    "PCB\n"
    "SCB:0\n"
    "STB\n"
    "U:magic:3254525889\n"
    "PM:3254525889\n"
    "SAB:uuid\n"
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
    "SAE\n"
    "U:stream_id:221\n"
    "STE\n"
    "SCE\n"
    "DST:221\n"
    "SCB:1\n"
    "STB\n"
    "U:packet_size:288\n"
    "EPTS:288\n"
    "U:content_size:272\n"
    "EPCS:272\n"
    "U:custom:65244\n"
    "STE\n"
    "SCE\n"
    "ERB\n"
    "ERT:0\n"
    "SCB:5\n"
    "STB\n"
    "STB:s\n"
    "U:a:16909060\n"
    "PB\n"
    "PCB\n"
    "SCB:0\n"
    "STB\n"
    "U:magic:3254525889\n"
    "PM:3254525889\n"
    "SAB:uuid\n"
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
    "SAE\n"
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
    "SUB:1:s\n"
    "SUB:3:alu\n"
    "SUB:2:t\n";

int main()
{
    auto traceType = yactfr::traceTypeFromMetadataText(metadata,
                                                       metadata + std::strlen(metadata));
    auto factory = std::make_shared<MemDataSourceFactory>(stream,
                                                          sizeof(stream), 3);
    yactfr::PacketSequence seq {traceType, factory};
    std::ostringstream ss;
    ElementPrinter printer {ss, 0};
    auto it = std::begin(seq);

    while (true) {
        if (it.offset() == 160) {
            // jump to third packet
            it.seekPacket(768 / 8);
        } else if (it.offset() == 1016) {
            // jump to second packet
            it.seekPacket(416 / 8);
        } else if (it.offset() == 664) {
            break;
        } else {
            it->accept(printer);
            ++it;
            continue;
        }
    }

    if (ss.str() == expected) {
        return 0;
    }

    std::cerr << "Expected:\n\n" << expected << "\n" <<
                 "Got:\n\n" << ss.str();
    return 1;
}
