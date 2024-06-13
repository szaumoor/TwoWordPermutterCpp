#ifndef CONSOLE_H
#define CONSOLE_H

#include <filesystem>
#include <chrono>

namespace console
{
   /// <summary>
   /// Terminates program if user input equals 'q'. The check is case-insensitive.
   /// </summary>
   ///
   /// <param name="line"> Line of input to check for 'q' </param>
    inline void exit_if_q( const std::string& line ) {
        if ( line.size() == 1 && tolower( line[0] ) == 'q' )
            quick_exit( 0 );
    }

    /// <summary>
    /// Gets user input for file path until a valid input is received.
    /// </summary>
    ///
    /// <returns> std::string of user input, which will be a valid file path or 'q' to quit. </returns>
    std::string file_input();

    /// <summary>
    /// Gets user input for char limit until a valid input is received (2 or greater).
    /// Incorrect input will result in a default value of 14.
    /// </summary>
    ///
    /// <returns> number of characters to limit the character limit of the permutations </returns>
    int get_char_limit();

    /// <summary>
    /// Gets the filename of the input file without the extension (if it has one).
    /// </summary>
    ///
    /// <returns> std::string of the filename </returns>
    inline std::string get_name( std::string& line ) {
        const auto it = line.find_last_of( '.' );
        return it == std::string::npos ? std::move( line ) : line.substr( 0, it ) + "_output.txt";
    }

    /// <summary>
    /// Gets nanosecond timestamp since epoch
    /// </summary>
    ///
    /// <returns> The number of nanoseconds since epoch as a 64-bit integer </returns>
    inline auto nanos() {
        const auto current_time = std::chrono::high_resolution_clock::now();
        const auto nanoseconds = std::chrono::time_point_cast<std::chrono::nanoseconds>(current_time);
        return nanoseconds.time_since_epoch().count();
    }
}

#endif