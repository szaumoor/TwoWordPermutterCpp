#include <iostream>
#include "console.h"

namespace console
{
    std::string file_input()
    {
        std::cout << "Enter file to process (Type 'q' to quit): ";
        std::string line;
        std::getline( std::cin, line );
        exit_if_q( line );

        while ( !exists( std::filesystem::path( line ) ) )
        {
            std::cout << "That file doesn't exist, try again (Type 'q' to quit): ";
            std::getline( std::cin, line );
            exit_if_q( line );
        }
        return line;
    }

    int get_char_limit() {
        std::cout << "Enter character limit for permutations: ";
        int limit;
        std::cin >> limit;

        if ( std::cin.bad() || limit < 2 ) {
            std::cout << "Invalid character limit. Setting to default 14.\n";
            return 14;
        }
        return limit;
    }
}