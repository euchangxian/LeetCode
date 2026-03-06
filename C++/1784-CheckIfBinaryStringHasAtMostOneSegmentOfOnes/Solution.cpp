#include <algorithm>
#include <ranges>
#include <string_view>

class Solution {
 public:
  bool checkOnesSegment(std::string_view s) {
    // Given binary string s without leading zeros, return true if s contains
    // at most one contiguous segment of ones.
    //
    // Lol. No leading zeros?
    // Find a "01" works too.
    return !std::ranges::contains(
        s | std::views::drop_while([](auto c) { return c == '1'; }), '1');
  }
};
