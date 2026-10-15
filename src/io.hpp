#ifndef TWOWORDPERMUTTERCPP_IO_HPP
#define TWOWORDPERMUTTERCPP_IO_HPP

#include "text.hpp"

#include <boost/algorithm/string/trim.hpp>

#include <algorithm>
#include <chrono>
#include <expected>
#include <filesystem>
#include <fstream>
#include <generator>
#include <string>
#include <vector>

namespace rng = std::ranges;
namespace vws = std::views;
namespace fs = std::filesystem;

namespace io
{
    static std::generator<const std::string&> lines(std::istream& input)
    {
        std::string line;
        while (std::getline(input, line))
        {
            if (!line.empty() && line.back() == '\r')
                line.pop_back();

            boost::trim(line);
            co_yield line;
        }
    }

    constexpr std::expected<std::vector<text::Word>, std::string> get_words( const fs::path& path ) {
        std::ifstream input{ path };
        if ( !input )
            return std::unexpected { "File opening failed" };

        auto words = io::lines( input ) |
            vws::filter( [](const auto& str) { return text::valid_line(str); }) |
            vws::transform( [](auto str) { return text::extract_word( std::move(str) );}) |
            rng::to<std::vector<text::Word>>();

        rng::sort( words, std::less{} );
        return words;
    }

    constexpr std::expected<void, std::string> write_perms( const fs::path& path, const std::vector<std::string>& words ) {
        std::ofstream output( path );
        if ( !output )
            return std::unexpected { "File at " + path.string() + " could not be created for writing." };

        std::ranges::for_each( words, [&] ( const auto& str ) { output << (str + "\n"); });
        if ( !output )
            return std::unexpected { "Errors were found when attempting to insert lines into file at " + path.string() };

        return {};
    }

    constexpr std::expected<fs::path, std::string> get_path( const std::string& line )
    {
        if ( not fs::exists( line ) )
            return std::unexpected { "Path " + line + " does not exist in the filesystem" };

        if ( not fs::is_regular_file( line ) )
            return std::unexpected { "Path " + line + " does not point to a regular file" };

        return { fs::path{line} };
    }

    constexpr auto nanos()
    {
        const auto current_time = std::chrono::high_resolution_clock::now();
        const auto nanoseconds  = std::chrono::time_point_cast<std::chrono::nanoseconds>( current_time );
        return nanoseconds.time_since_epoch().count();
    }

} // end namespace io_utils

#endif //TWOWORDPERMUTTERCPP_IO_HPP
