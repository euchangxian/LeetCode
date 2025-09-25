#include <bitset>
#include <string>
#include <string_view>

using CharSet = std::bitset<128>;
constexpr auto toCharSet = [](std::string_view s) {
  CharSet set;
  for (char c : s) {
    set.set(c);
  }
  return set;
};

class Solution {
 public:
  std::string longestNiceSubstring(std::string_view s) {
    // A string s is nice if for every letter of the alphabet that s contains,
    // it appears in both upper and lowercase.
    // Given s, return the longest substring of s that is nice.
    // Tie-break by earliest occurence.
    //
    // Given constraints, n <= 100, we can enumerate all possible subtrings.
    // Sliding Window is NOT a possible solution - we cant determine if, when
    // a window is valid, that the leftmost character can be excluded from
    // subsequent answers.
    const auto n = static_cast<int>(s.size());

    auto set = toCharSet(s);
    for (int i = 0; i < n; ++i) {
      if (auto c = s[i]; set[std::toupper(c)] && set[std::tolower(c)]) {
        continue;
      }

      // If the current character does not have both upper and lower in the
      // substring, then split s such that we get left|i|right.
      auto sub1 = longestNiceSubstring(s.substr(0, i));
      auto sub2 = longestNiceSubstring(s.substr(i + 1));
      if (sub1.size() >= sub2.size()) {
        return sub1;
      }
      return sub2;
    }
    return std::string{s};
  }
};
