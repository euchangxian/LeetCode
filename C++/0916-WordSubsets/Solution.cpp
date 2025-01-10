#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdlib>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

class Solution {
 public:
  std::vector<std::string> wordSubsets(std::vector<std::string>& words1,
                                       std::vector<std::string>& words2) {
    // A string b is considered a subset of a if every letter in b occurs in a.
    // Counts must match.
    // A string a from words1 is universal if every string b in words2 is a
    // subset of a.
    //
    // Naively, O(nm), where n = words1.length, m = words2.length.
    // O(mL) to determine the frequency array of each word in words2. Then
    // O(nL * 26m) to check each.
    // Can we do better?
    //
    // Instead of checking against each frequency array, we can
    // aggregate the required frequency, by taking the max frequency of each
    // character.
    // This is because if the multiplicity of 'a' in bi is greater than bj,
    // then ak must contain at least bi['a'] times of 'a'.
    // Now, the time complexity is reduced to: O(mL + nL * 26)
    // Can we do better?
    // Not sure.

    std::array<int, 26> required{};
    for (std::string_view word : words2) {
      std::array<int, 26> frequency{};
      for (char c : word) {
        required[c - 'a'] = std::max(required[c - 'a'], ++frequency[c - 'a']);
      }
    }

    auto universal = [&required](std::array<int, 26>& frequency) -> bool {
      for (int i = 0; i < 26; ++i) {
        if (frequency[i] < required[i]) {
          return false;
        }
      }
      return true;
    };

    std::vector<std::string> result;
    result.reserve(words1.size());
    // iterate using string reference so we can move the string instead of
    // constructing one from a string view.
    for (std::string& word : words1) {
      std::array<int, 26> frequency{};
      for (char c : word) {
        ++frequency[c - 'a'];
      }

      if (universal(frequency)) {
        result.push_back(std::move(word));
      }
    }

    return result;
  }
};
