#include "text.hpp"
#include "io.hpp"

#include <algorithm>
#include <cctype>
#include <iterator>
#include <ranges>
#include <string>
#include <vector>

namespace vws = std::views;
namespace rng = std::ranges;

namespace text
{
    static std::string& delete_last_char( std::string& line ) noexcept
    {
        if ( line.size() < 2 )
            return line;

        line.pop_back();
        return line;
    }

    static constexpr
    bool is_alliteration( const std::string& first_word, const std::string& second_word ) noexcept
    {
        const auto second_word_front = toupper( second_word.front() );

        const auto firsts_match     = toupper( first_word.front() ) == second_word_front;
        const auto last_first_match = toupper( first_word.back() ) == second_word_front;

        return firsts_match || last_first_match;
    }

    static constexpr bool valid_second_word( const Word& first_word, const Word& second_word ) noexcept
    {
        return second_word.type != Word::Order::First && first_word.content != second_word.content
               && !is_alliteration( first_word.content, second_word.content)
        ;
    }

    bool operator<( const Word& word1, const Word& word2 ) noexcept
    {
        return word1.content < word2.content;
    }

    std::vector<std::string> generate_permutations( const std::vector<Word>& words, const std::size_t limit_exclusive )
    {
        std::vector<std::string> perm_words;
        int64_t perm_count { 0 };
        for ( const auto& first : words | vws::filter( [](const Word& w) { return w.type != Word::Order::Second;}) )
        {
            auto applicable_words = words
                | vws::filter( [&]( const Word& w ) noexcept {
                    return valid_second_word( first, w );
                } )
                | vws::transform( [&]( const Word& w ) noexcept {
                    return first.content + w.content;
                } )
                | vws::filter( [=]( const std::string& str ) noexcept {
                    return limit_exclusive == 0 || str.size() <= limit_exclusive;
                } );

            const auto distance = std::distance( applicable_words.begin(), applicable_words.end() );
            if ( distance == 0 )
                continue;
            perm_words.emplace_back(
                "Permutations starting with " + first.content + "\n" + "------------------------------------" );
            perm_count += distance;
            rng::move( applicable_words, std::back_inserter( perm_words ) );
            perm_words.emplace_back( "\n" );
        }
        perm_words.emplace_back( "------------------------------------\n"
                                 "A total of " + std::to_string( perm_count ) +
                                 " valid permutations were discovered" );
        return perm_words;
    }

    Word extract_word( std::string line ) noexcept
    {
        switch ( line.back() )
        {
            case '#': return Word{ .content=delete_last_char( line ), .type=Word::Order::First  };
            case '*': return Word { .content=delete_last_char( line ), .type=Word::Order::Second };
            default: return Word { .content=line };
        }
    }
} // end namespace text
