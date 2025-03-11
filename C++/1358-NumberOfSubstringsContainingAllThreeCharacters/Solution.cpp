#include <array>
#include <cstddef>
#include <cstdlib>
#include <string_view>

class Solution {
 public:
  int numberOfSubstrings(std::string_view s) {
    // Contain at least one occurence of all of a|b|c
    // Seems similar to at least one of each vowel and k consonants question.
    // Oh but the string s contains ONLY a|b|c.
    // i.e., if we can find the first suffix occurence of the other 2
    // characters, then we can maff it out.
    // can we sliding-window ts?
    auto valid = [](std::array<int, 26>& frequency) -> bool {
      return frequency[0] > 0 && frequency[1] > 0 && frequency[2] > 0;
    };

    int result = 0;
    std::array<int, 26> frequency{};
    int l = 0;
    for (int r = 0; r < s.size(); ++r) {
      ++frequency[s[r] - 'a'];

      while (valid(frequency)) {
        // can form substrings with each character to the right.
        result += s.size() - r;
        --frequency[s[l++] - 'a'];
      }
    }
    return result;
  }
};
