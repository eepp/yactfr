/*
 * Copyright (C) 2026 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <clocale>
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <string>

#include <yactfr/yactfr.hpp>

namespace {

/*
 * Returns the message of the text parse error which
 * yactfr::fromMetadataText() throws when parsing [`begin`, `end`[, or
 * an empty string if it doesn't throw.
 */
std::string parseErrorMsg(const char * const begin, const char * const end)
{
    try {
        yactfr::fromMetadataText(begin, end);
    } catch (const yactfr::TextParseError& exc) {
        return exc.what();
    }

    return {};
}

/*
 * Checks that parsing the first `len` characters of `buf` gives the
 * same parse error as parsing a copy of those characters
 * (null-terminated by `std::string`), that is, that the parser doesn't
 * read the characters of `buf` after its end.
 */
bool checkRange(const char * const name, const std::string& buf, const std::size_t len)
{
    const std::string text {buf, 0, len};
    const auto expectedMsg = parseErrorMsg(text.data(), text.data() + text.size());

    if (expectedMsg.empty()) {
        std::cerr << name << ": no parse error with the NUL-terminated text\n";
        return false;
    }

    if (const auto msg = parseErrorMsg(buf.data(), buf.data() + len); msg != expectedMsg) {
        std::cerr << name << ": unexpected parse error: `" << msg << "` (expecting `" <<
                     expectedMsg << "`)\n";
        return false;
    }

    return true;
}

/*
 * Checks that parsing a real number doesn't depend on `LC_NUMERIC`.
 */
bool checkRealLocale()
{
    /*
     * Try a few locales having `,` as their decimal separator.
     *
     * Skip the check if none is available.
     */
    const char *locale = nullptr;

    for (const auto name : {"fr_FR.UTF-8", "fr_FR.utf8", "fr_FR", "de_DE.UTF-8", "de_DE.utf8",
                            "de_DE"}) {
        if (std::setlocale(LC_NUMERIC, name)) {
            locale = name;
            break;
        }
    }

    if (!locale) {
        std::cout << "real-locale: skipped (no locale having `,` as its decimal separator)\n";
        return true;
    }

    const std::string text {
        "\x1e{\"type\": \"preamble\", \"version\": 2}"
        "\x1e{\"type\": \"trace-class\", \"attributes\": {\"r\": 1.5}}"
        "\x1e{\"type\": \"data-stream-class\"}"
    };

    auto ok = true;

    try {
        const auto traceType = yactfr::fromMetadataText(text).first;
        const auto item = (*traceType->attributes())["r"];

        if (!item || !item->isReal() || *item->asReal() != 1.5) {
            std::cerr << "real-locale (" << locale << "): unexpected `r` attribute\n";
            ok = false;
        }
    } catch (const std::exception& exc) {
        std::cerr << "real-locale (" << locale << "): unexpected exception: " << exc.what() << "\n";
        ok = false;
    }

    std::setlocale(LC_NUMERIC, "C");
    return ok;
}

} // namespace

int main()
{
    auto ok = true;

    /*
     * Each buffer contains a metadata text of which the last token is a
     * number, followed with more digits which aren't part of the range
     * to parse.
     */
    {
        const std::string buf {
            "/* CTF 1.8 */\n"
            "trace { major = 1; minor = 8; byte_order = le; };\n"
            "env { x = 1"
        };

        ok = checkRange("tsdl-int", buf + "23; };\n", buf.size()) && ok;
    }

    {
        const std::string buf {"\x1e{\"type\": \"preamble\", \"version\": 2"};

        ok = checkRange("json-int", buf + "0}", buf.size()) && ok;
    }

    {
        const std::string buf {
            "\x1e{\"type\": \"preamble\", \"version\": 2}"
            "\x1e{\"type\": \"trace-class\", \"attributes\": {\"r\": 1.5"
        };

        ok = checkRange("json-real", buf + "23}}", buf.size()) && ok;
    }

    ok = checkRealLocale() && ok;
    return ok ? 0 : 1;
}
