/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <yactfr/yactfr.hpp>

int main(const int argc, const char * const argv[])
{
    assert(argc >= 2);

    std::string tracePath {argv[1]};
    std::ifstream file {tracePath + "/metadata"};
    const auto metadataStream = yactfr::createMetadataStream(file);
    const auto traceTypeEnvPair = yactfr::fromMetadataText(metadataStream->text());

    assert(traceTypeEnvPair.second.entries().empty());

    yactfr::MemoryMappedFileViewFactory factory {tracePath + "/stream", 4096};
    yactfr::TraceEnvironmentStreamDecoder decoder {*traceTypeEnvPair.first, factory};

    try {
        const auto env = decoder.decode();

        for (auto& entry : env.entries()) {
            std::cout << entry.first << ": ";

            if (const auto val = boost::get<long long>(&entry.second)) {
                std::cout << *val;
            } else {
                std::cout << boost::get<std::string>(entry.second);
            }

            std::cout << std::endl;
        }
    } catch (const yactfr::InvalidTraceEnvironmentStream& exc) {
        std::cout << exc.what() << std::endl;
    }

    return 0;
}
