#include "io.h"
#include "text.h"

#include <boost/algorithm/string/trim.hpp>

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace io_utils
{
	using namespace text;
	constexpr std::string_view k_comment_mark = "//"; // Lines that start with this are ignored

	namespace // Private
	{
		bool ValidLine( const std::string& line ) noexcept {
			return !line.empty() && !line.starts_with( k_comment_mark );
		}
	}

    std::vector<Word> GetWords( const std::string& path ) {
        std::ifstream input{ path };
		if ( !input ) {
            std::cerr << "Sorry, file opening failed.\n";
			std::quick_exit( 1 );
		}
        std::vector<Word> parsed_words;
		parsed_words.reserve( 150U );
		
		for ( std::string line; getline( input, line );) {
			boost::trim( line );
			if ( ValidLine( line ) ) {
				parsed_words.emplace_back(ExtractWord( std::move(line )) );
			}
		}
		std::sort( parsed_words.begin(), parsed_words.end());
		return parsed_words;
	}

	void WritePerms( const std::string& path, const std::vector<std::string>& words ) {
        std::ofstream output( path );
		if ( !output ) {
            std::cerr << "Sorry, file writing failed.\n";
			std::quick_exit( 1 );
		}
        std::ranges::for_each( words, [&] ( const auto& str ) { output << (str + "\n"); });
	}
} // end namespace io_utils