#include <cstddef>
#include <cstdlib>
#include <string>
#include <string_view>
#include <vector>

class Solution {
 public:
  std::vector<std::string> stringMatching(std::vector<std::string>& words) {
    // Return all words that is a substring of another word.
    // Naively, O(n^2 * L^2), compare each string with every other string in
    // O(L^2) time.
    // Can we do better?
    // KMP... instead of naive string matching.
    std::vector<std::string> result;
    result.reserve(words.size());
    for (int i = 0; i < words.size(); ++i) {
      for (int j = 0; j < words.size(); ++j) {
        if (i == j) {
          continue;
        }

        std::string_view curr{words[i]};
        std::string_view next{words[j]};
        if (next.contains(curr)) {
          result.emplace_back(words[i]);
          break;  // Only want to push this word once.
        }
      }
    }
    return result;
  }
};
