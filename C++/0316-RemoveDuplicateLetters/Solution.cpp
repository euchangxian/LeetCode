#include <array>
#include <bitset>
#include <string>
#include <string_view>

class Solution {
 public:
  std::string removeDuplicateLetters(std::string_view s) {
    // Duplicate of 1081 - Smallest Subsequence of Distinct Characters.
    const auto n = static_cast<int>(s.size());

    std::array<int, 256> freq{};
    for (auto c : s) {
      ++freq[c];
    }

    std::bitset<256> seen{};
    std::string sorted;
    sorted.reserve(n);
    for (auto c : s) {
      --freq[c];

      if (seen.test(c)) {
        continue;
      }

      while (!sorted.empty() && sorted.back() > c && freq[sorted.back()] > 0) {
        seen.reset(sorted.back());
        sorted.pop_back();
      }

      sorted.push_back(c);
      seen.set(c);
    }

    return sorted;
  }
};
