/*
 * Copyright (C) 2017-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <yactfr/metadata/trace-type-from-metadata-text.hpp>
#include <yactfr/metadata/metadata-stream.hpp>
#include <yactfr/metadata/io.hpp>

int main(int argc, const char* argv[])
{
    try {
        std::ifstream file {argv[1]};
        auto metadataStream = yactfr::createMetadataStream(file);
        auto traceType = yactfr::traceTypeFromMetadataText(std::begin(metadataStream->text()),
                                                           std::end(metadataStream->text()));
        std::cout << *traceType << std::endl;
    } catch (const yactfr::MetadataParseError& ex) {
        std::cerr << ex.what() << std::endl;
        return 2;
    } catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
