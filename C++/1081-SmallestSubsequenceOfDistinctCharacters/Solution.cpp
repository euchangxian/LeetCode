#include <array>
#include <bitset>
#include <string>
#include <string_view>

class Solution {
 public:
  std::string smallestSubsequence(std::string_view s) {
    // Given string s, return the lexicographically smallest subsequence of s
    // that contains all the distinct characters of s exactly once.
    //
    // Hm. We take the ith occurence of a character only if the existing
    // occurence is not sorted relatively?
    // Two passes?
    // s.length <= 1000.
    // Hm...
    // If the subsequence is sorted, then we won't take any subsequent repeat
    // occurences.
    // If not sorted, how do we detected which character?
    // Two sets?
    // - One for has occurence, i.e., seen.
    // - One for in sorted-subsequence (mono-stack).
    // Use mono-increasing stack.
    // If a character will break the monotonicity, AND there are still
    // occurences LATER in the string, remove the problematic one.
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
