#ifndef TWOWORDPERMUTTERCPP_CONSOLE_HPP
#define TWOWORDPERMUTTERCPP_CONSOLE_HPP

#include <expected>
#include <filesystem>
#include <string>
#include <utility>

#include "io.hpp"

namespace console
{
    using ExtractedArgs = std::expected<std::pair<std::filesystem::path, uint>, std::string>;

    static constexpr auto kNoArgError = "No arguments provided. Please provide a path (relative or absolute) "
                                    "followed if desired by an optional integer (N>2) for character limits "
                                    "for the permutations (limitless by default)";

    static constexpr std::expected<int,std::string> parse_char_limit( const std::string_view str ) noexcept
    {
        int int_parse {0};
        if ( const auto well_parsed = std::from_chars(str.data(), str.data()+str.size(), int_parse);
            not well_parsed )
        {
            return std::unexpected { "The following value could not be parsed as an integer: '" + std::string(str) + "'" };
        }

        if ( int_parse < 3 )
            return std::unexpected { std::to_string(int_parse) + " is not a valid N character limit (N > 2)" };

        return { int_parse };
    }

    static ExtractedArgs parse_args(auto argc, auto argv) noexcept
    {
        if (argc == 1)
            return std::unexpected {kNoArgError };

        const auto path = io::get_path( argv[1] );
        if (!path)
            return std::unexpected { path.error() };

        int char_limit = 0;
        if ( argc >= 3)
        {
            const std::string_view char_arg = argv[2];
            if ( const auto parsed = parse_char_limit( char_arg ); not parsed )
                return std::unexpected { parsed.error() };
            else
                char_limit = parsed.value();
        }

        return { std::make_pair( path.value(), char_limit ) };
    }
}

#endif //TWOWORDPERMUTTERCPP_CONSOLE_HPP
