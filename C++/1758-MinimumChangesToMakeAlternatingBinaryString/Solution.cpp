#include <algorithm>
#include <string_view>
#include <utility>

class Solution {
 public:
  int minOperations(std::string_view s) {
    // Binary string s.
    // In one operation, change any '0' to '1' and vice versa.
    // Return the minimum operation to make s alternating - no two adjacent
    // characters are equal.
    //
    // Greedy? 110, will fail because 110 -> 100 -> 101 instead of 010.
    // Start with 0, or start with 1.
    auto countMismatch = [&](auto start) {
      auto result = 0;
      for (char c : s) {
        result += (c - '0') != std::exchange(start, 1 - start);
      }
      return result;
    };

    auto startWithZero = countMismatch(0);
    auto startWithOne = static_cast<int>(s.size()) - startWithZero;
    return std::min(startWithZero, startWithOne);
  }
};
