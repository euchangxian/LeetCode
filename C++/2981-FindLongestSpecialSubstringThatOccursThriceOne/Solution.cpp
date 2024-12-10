#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdlib>
#include <string>
#include <string_view>

class Solution {
 public:
  int maximumLength(std::string_view s) {
    // special iff made of a single character.
    // Want: Longest special substring that occurs at least
    // thrice.
    // Given that the minimum requirement is a single character
    // that occurs thrice, we can enumerate over special substring lengths.
    std::array<int, 26> count{};
    for (char c : s) {
      ++count[c - 'a'];
    }

    auto atLeastThree = [](int freq) -> bool { return freq >= 3; };
    if (std::none_of(count.begin(), count.end(), atLeastThree)) {
      return -1;
    }

    // for each special substring of length l, find the number of occurences.
    // Since each special substring consists of the same characters, we can
    // simply form the target substring and count.
    int maxLength = 1;
    for (int l = 2; l <= s.size(); ++l) {
      for (char c = 'a'; c <= 'z'; ++c) {
        std::string target = std::string(l, c);
        std::string_view sv{target.begin(), target.end()};

        int freq = 0;

        // for each start, check equal and increment freq
        for (int start = 0; start + target.size() <= s.size(); ++start) {
          if (s.substr(start, l) == sv) {
            ++freq;
          }
        }

        if (freq >= 3) {
          maxLength = l;
        }
      }
    }

    return maxLength;
  }
};
