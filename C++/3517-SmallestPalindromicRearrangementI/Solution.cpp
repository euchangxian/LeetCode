#include <array>
#include <ranges>
#include <string>

class Solution {
 public:
  std::string smallestPalindrome(std::string s) {
    // Return the lexicographically smallest palindromic permutation of s.
    const auto n = static_cast<int>(s.size());
    const auto mid = n / 2;

    std::array<int, 26> freq{};
    for (auto c : s | std::views::take(mid)) {
      ++freq[c - 'a'];
    }

    auto left = 0;
    auto right = n - 1;
    for (auto i = 0; i < 26; ++i) {
      auto& count = freq[i];
      while (count--) {
        auto c = i + 'a';
        s[left++] = c;
        s[right--] = c;
      }
    }
    return s;
  }
};
