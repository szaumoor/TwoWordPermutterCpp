#include "text.h"
#include "io.h"

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <iterator>
#include <ranges>
#include <string>
#include <vector>
#include <type_traits>

namespace text
{
    using namespace std;
    namespace // Private
    {
        string&& DeleteSuffix( string&& line ) noexcept {
            if ( line.size() < 2 ) return std::move(line);
            line.pop_back();
            return std::move(line);
        }
        bool Alliteration( const string& first_word, const string& second_word ) noexcept {
            const auto second_word_front = toupper( second_word.front() );

            const auto firsts_match = toupper( first_word.front() ) == second_word_front;
            const auto last_first_match = toupper( first_word.back() ) == second_word_front;

            return firsts_match || last_first_match;
        }

        bool ValidSecondWord( const Word& first_word, const Word& second_word ) noexcept {
            return second_word.type != Word::Type::k_first_word && first_word.content != second_word.content
                && !Alliteration( first_word.content, second_word.content );
        }
    }

    Word::Word( string content, const Type type ) noexcept
        : content( std::move(content) ), type( type ) {}

     Word ExtractWord( string&& line ) noexcept {
         switch (line.back())
         {
         case io_utils::k_first_word_mark: return Word(DeleteSuffix(std::move(line)), Word::Type::k_first_word);
             case io_utils::k_second_word_mark: return Word(DeleteSuffix(std::move(line)), Word::Type::k_second_word);
             default: return Word(std::move(line));
         }
     }

    bool operator<( const Word& word1, const Word& word2 ) noexcept {
        return word1.content < word2.content;
    }

    vector<string> GeneratePermutations( vector<Word>&& words, const size_t limit_exclusive ) {
        using views::filter;
        using views::transform;

        const auto words_size = words.size();
        vector<string> perm_words;
        perm_words.reserve( 1 + words_size * (words_size - 1) + 2 * words_size );

        int64_t perm_count = 0;
        for ( const auto& first : words ) {
            if ( first.type == Word::Type::k_second_word ) continue;
            auto applicable_words = words
                | filter( [&] ( const Word& w ) noexcept  { return ValidSecondWord( first, w ); } ) 
                | transform( [&] ( const Word& w ) noexcept { return first.content + w.content; } )
                | filter( [=] ( const string& str ) noexcept { return str.size() <= limit_exclusive; } );

            const auto distance = std::distance( applicable_words.begin(), applicable_words.end() );
            if ( distance == 0 ) continue;
            perm_words.emplace_back( "Permutations starting with " + first.content + "\n" + "------------------------------------" );
            perm_count += distance;
            ranges::move( applicable_words, std::back_inserter( perm_words ) );
            perm_words.emplace_back( "\n" );
        }
        perm_words.emplace_back( "------------------------------------\n" 
                                 "A total of " + std::to_string( perm_count ) +
                                " valid permutations were discovered" );
        return perm_words;
    }
} // end namespace text
