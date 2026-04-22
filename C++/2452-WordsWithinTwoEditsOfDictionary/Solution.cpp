#include <ranges>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

class Solution {
 public:
  std::vector<std::string> twoEditWords(std::vector<std::string>& queries,
                                        std::vector<std::string>& dictionary) {
    // All words are lowercase english letters, all same length.
    // In one edit:
    // - take a word from queries, change any letter in it to any other letter.
    // Find all words from queries that after a maximum of two edits, is
    // equal to some word from dictionary.
    // Return the words in the same order they appear in queries.
    //
    // - queries.length, dictionary.length <= 100
    // - word.length == n <= 100
    // Constraints are small.
    //
    // We can edit each word twice.
    // O(N^2 * L) is trivial?
    // for each word_q in queries:
    //   for each word_d in dictionary:
    //     checkIfCanMakeWord_D(word_q) // two pointer approach.
    constexpr auto canEditIntoWord = [](std::string_view source,
                                        std::string_view target) {
      auto edits = 2;
      for (auto [s, t] : std::views::zip(source, target)) {
        if (s != t) {
          if (--edits < 0) {
            return false;
          }
        }
      }
      return true;
    };

    std::vector<std::string> result;
    result.reserve(queries.size());
    for (auto& source : queries) {
      for (const auto& target : dictionary) {
        if (canEditIntoWord(source, target)) {
          result.emplace_back(std::move(source));
          break;
        }
      }
    }
    return result;
  }
};
