/*
 * Copyright (C) 2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_TESTS_COMMON_TRACE_HPP
#define _YACTFR_TESTS_COMMON_TRACE_HPP

#include <cstdint>

namespace {

constexpr auto metadata =
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
    "  event.header := struct {"
    "    u8 id;"
    "  };"
    "};"
    "event {"
    "  stream_id = 0xdd;"
    "  id = 0x11;"
    "  fields := struct {"
    "    struct {"
    "      u32 a;"
    "      u16 b;"
    "      u8 c;"
    "    } s;"
    "  };"
    "};"
    "event {"
    "  stream_id = 0xdd;"
    "  id = 0x22;"
    "  context := struct {"
    "    u8 len;"
    "  };"
    "  fields := struct {"
    "    string strings[event.context.len];"
    "  };"
    "};";

constexpr std::uint8_t stream[] = {
    // packet header
    0xc1, 0xfc, 0x1f, 0xc1,
    0x64, 0xdf, 0x60, 0x8e, 0x8d, 0xb9, 0x4f, 0xed,
    0x9c, 0x50, 0x0e, 0xb9, 0x72, 0x39, 0x2c, 0xf7,
    0xdd,

    // packet context
    0x02, 0x48, 0x02, 0x28, 0x11, 0xd2,

    // event record
    0x11, 0xaa, 0xbb, 0xcc, 0xdd, 0xde, 0xad, 0xff,

    // event record
    0x11, 0x12, 0x12, 0x23, 0x23, 0x44, 0x55, 0x66,

    // event record
    0x22, 3,
    'a', 'l', 'e', 'r', 't', 0,
    'l', 'o', 'o', 'k', 0,
    's', 'o', 'u', 'r', 0,

    // event record
    0x11, 0x18, 0x19, 0x11, 0x0e, 0xf2, 0x43, 0x51,

    // padding
    0xff, 0x00, 0xf0, 0x0f,

    // packet header
    0xc1, 0xfc, 0x1f, 0xc1,
    0x64, 0xdf, 0x60, 0x8e, 0x8d, 0xb9, 0x4f, 0xed,
    0x9c, 0x50, 0x0e, 0xb9, 0x72, 0x39, 0x2c, 0xf7,
    0x23,

    // packet context
    0x01, 0x60, 0x01, 0x60,

    // event record
    's', 'a', 'l', 'u', 't', 0, 0x44, 0x55, 0x66, 0x77,

    // event record
    'C', 'o', 'l', 'a', 0, 0x44, 0x55, 0x66, 0x77,

    // packet header
    0xc1, 0xfc, 0x1f, 0xc1,
    0x64, 0xdf, 0x60, 0x8e, 0x8d, 0xb9, 0x4f, 0xed,
    0x9c, 0x50, 0x0e, 0xb9, 0x72, 0x39, 0x2c, 0xf7,
    0xdd,

    // packet context
    0x01, 0x80, 0x01, 0x70, 0xfe, 0xdc,

    // event record
    0x22, 2,
    'd', 'r', 'y', 0,
    't', 'h', 'a', 'w', 0,

    // event record
    0x11, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,

    // padding
    0x11, 0x22,
};

} // namespace

#endif // _YACTFR_TESTS_COMMON_TRACE_HPP
