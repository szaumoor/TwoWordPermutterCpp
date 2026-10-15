#include "io.hpp"
#include "text.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "console.hpp"

int main( const int argc, const char* argv[] )
{
    const auto resolved_args = console::parse_args(argc, argv);
    if (not resolved_args)
    {
        std::cerr << resolved_args.error() << '\n';
        return EXIT_FAILURE;
    }

    const auto& [path, char_limit] = resolved_args.value();
    const auto extracted_words = io::get_words( path );

    if (not extracted_words)
    {
        std::cerr << extracted_words.error() << '\n';
        return EXIT_FAILURE;
    }

    const auto permutations = text::generate_permutations( extracted_words.value(), char_limit );

    const auto new_file_name = path.stem().string() + "_output" + "(" + std::to_string(char_limit) + ")_" + std::to_string(
        io::nanos()) +  +".txt";

    if ( const auto success = io::write_perms(path.parent_path() / new_file_name, permutations );
         not success
    ) {
        std::cerr << success.error() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
