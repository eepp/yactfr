/*
 * Copyright (C) 2017-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <iostream>
#include <fstream>
#include <yactfr/yactfr.hpp>

int main(int, const char * const argv[])
{
    try {
        std::ifstream file {argv[1]};
        const auto metadataStream = yactfr::createMetadataStream(file);

        yactfr::fromMetadataText(metadataStream->text());
    } catch (const yactfr::TextParseError& ex) {
        std::cout << ex.what();
    } catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
