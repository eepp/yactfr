/*
 * Copyright (C) 2017-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <yactfr/yactfr.hpp>

int main(const int argc, const char * const argv[])
{
    try {
        std::ifstream file {argv[1]};
        const auto metadataStream = yactfr::createMetadataStream(file);
        yactfr::fromMetadataText(metadataStream->text().begin(), metadataStream->text().end());
    } catch (const yactfr::TextParseError& ex) {
        std::cerr << ex.what() << std::endl;
        return 2;
    } catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
