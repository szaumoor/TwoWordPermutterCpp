#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <vector>

namespace text
{
    static bool valid_line( const std::string& line ) noexcept {
        constexpr static auto kCommentMark = "//";
        return !line.empty() && !line.starts_with( kCommentMark );
    }

    /**
     * Struct to encapsulate one part of a combination of two words, and a classification
     * in terms of whether they should be determined to be only usable as first word,
     * second word, or either.
     */
    struct Word
    {
        /**
         * Specific ordering set to a word for the purposes of generating permutations
         */
        enum struct Order { First, Second, FirstOrSecond };

        std::string content{};
        Order type { Order::FirstOrSecond };
        friend bool operator<( const Word& word1, const Word& word2 ) noexcept;
    };

    /**
     * Generates the possible permutations of a list of eligible words with an user-imposed character limit.
     *
     * @param words Vector of words
     * @param limit_exclusive Limit of characters before a word can be accepted
     * @return A vector of strings with said combinations
     */
    std::vector<std::string> generate_permutations( const std::vector<Word>& words, size_t limit_exclusive );


    Word extract_word( std::string line ) noexcept;
} // end namespace words
#endif
