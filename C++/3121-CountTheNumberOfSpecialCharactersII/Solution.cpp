#include <algorithm>
#include <array>
#include <ranges>
#include <string_view>

class Solution {
 public:
  int numberOfSpecialChars(std::string_view word) {
    // given string word.
    // A letter c is special if it appears both in lower and upper case, and
    // every lower case occurence appears before the first upper case.
    //
    // Can track last-seen lower, first-seen upper.
    const auto n = static_cast<int>(word.size());
    std::array<int, 26> lower;
    std::array<int, 26> upper;

    std::ranges::fill(lower, n);
    std::ranges::fill(upper, n);

    for (auto i = 0; i < n; ++i) {
      auto c = word[i];
      if (c >= 'a') {
        lower[c - 'a'] = i;
      } else {
        upper[c - 'A'] = std::min(upper[c - 'A'], i);
      }
    }

    return std::ranges::count_if(std::views::zip(lower, upper),
                                 [n](const auto lu) {
                                   auto [l, u] = lu;
                                   if (u == n) {
                                     // Only need to check upper, since l < u
                                     // will rule out n < n
                                     return false;
                                   }
                                   return l < u;
                                 });
  }
};
