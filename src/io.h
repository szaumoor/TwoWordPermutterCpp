#ifndef IO_H
#define IO_H

#include "text.h"

#include <string>
#include <vector>

/// <summary>
/// This namespace groups all IO operation required for this program.
/// </summary>
namespace io_utils
{
	constexpr char k_first_word_mark = '#'; // Names should have this as trailing character to qualify as first words
	constexpr char k_second_word_mark = '*'; // Names should have this as trailing character to qualify as second words
	/// <summary>
	/// Extracts Word objects from the provided text file in the path.
	/// </summary>
	/// <param name="path">The path to the text file</param>
	/// <returns>A vector containing the Word objects</returns>
    std::vector<text::Word> GetWords( const std::string& path );

	/// <summary>
	/// Writes out a list of strings into a text file.
	/// </summary>
	/// <param name="path">The output path</param>
	/// <param name="words">The vector of strings to write out</param>
	void WritePerms( const std::string& path, const std::vector<std::string>& words );
} // end namespace io_utils
#endif