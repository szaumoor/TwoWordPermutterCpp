#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <vector>

/// <summary>
///		This namespace groups text operations and constants needed for the program to parse the text and make the permutations.
/// </summary>
namespace text {
	/// <summary>
	///  Basic struct that encapsulates a 'Word' in this program, 
	///  which is a string that is marked as first-Word-only,
	/// second-Word-only, or position-agnostic. If Word type is not
	/// assigned, it is considered as word_type::k_any_word
	/// </summary>
	struct Word
	{
		enum class Type
		{
			k_any_word, // This is the basic flag indicating a Word is position agnostic, no trailing character needed
			k_first_word, // Always must be the first Word in the permutation
			k_second_word // Always must be the second Word in the permutation
		};
		std::string content;
		Type type;
		explicit Word( std::string content, Type type = Type::k_any_word ) noexcept;
		friend bool operator<( const Word& word1, const Word& word2 ) noexcept;
        Word(const Word& other) = default;
        Word(Word&& other) noexcept
            : content(std::move(other.content)),
              type(other.type)
        {
        }

        Word& operator=(const Word& other) = default;

        Word& operator=(Word&& other) noexcept
        {
            if (this == &other)
                return *this;
            content = std::move(other.content);
            type = other.type;
            return *this;
        }
    };

	/// <summary>
	/// Generates all the combinations possible in between the words of the passed vector,
	/// according to various rules, and with a particular character limit.
	/// </summary>
	/// <param name="words">A vector of Word objects.</param>
	/// <param name="limit_exclusive">A limit which will determine what combinations of Words will be valid.</param>
	/// <returns>A vector of strings containing all the possible combinations.</returns>
	std::vector<std::string> GeneratePermutations(std::vector<Word>&& words, size_t limit_exclusive );

	/// <summary>
	/// Computes what type of Word the passed string is according to
	/// trailing characters.
	/// </summary>
	/// <param name="line"> The string to be parsed </param>
	/// <returns>The Word object that results from the parsing</returns>
	Word ExtractWord( std::string&& line ) noexcept;
} // end namespace words
#endif