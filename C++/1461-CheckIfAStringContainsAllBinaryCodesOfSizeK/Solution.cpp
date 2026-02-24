#include <bitset>
#include <iterator>
#include <ranges>
#include <string_view>

constexpr auto MAX_K = 20;
constexpr auto MAX_NUMS = 1 << MAX_K;
class Solution {
 public:
  bool hasAllCodes(std::string_view s, int k) {
    // Given a binary string s:
    // return true if every binary code of length k is a substring of s.
    //
    // Enumerate?
    // k<=20 => 2^20 => 1million. Quite possible.
    // KMP to preprocess?
    // Rolling Hash of each K-length window in s? Not exactly necessary though.
    // Can just store integers. Lol.
    auto kMask = (1 << k) - 1;

    auto window = 0;
    std::bitset<MAX_NUMS + 1> present;
    for (int i = 0; i < s.size(); ++i) {
      auto b = s[i] - '0';
      window = ((window << 1) | b) & kMask;
      if (i >= k - 1) {
        present.set(window);
      }
    }

    return std::ranges::distance(
               std::views::iota(0, 1 << k) |
               std::views::filter([&](auto x) { return !present[x]; })) == 0;
  }
};
