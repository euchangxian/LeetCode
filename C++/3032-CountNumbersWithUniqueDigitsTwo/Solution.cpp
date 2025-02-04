#include <array>
#include <bitset>
#include <cstddef>
#include <cstdlib>

constexpr auto hasUniqueDigit = [](int n) -> bool {
  std::bitset<10> seen{};
  while (n) {
    int digit = n % 10;
    if (seen[digit]) {
      return false;
    }
    seen[digit] = true;
    n /= 10;
  }
  return true;
};

constexpr std::array<int, 1001> dp = []() -> std::array<int, 1001> {
  std::array<int, 1001> dp{};
  dp[1] = 1;
  for (int i = 2; i <= 1000; ++i) {
    dp[i] = dp[i - 1] + hasUniqueDigit(i);
  }
  return dp;
}();

class Solution {
 public:
  int numberCount(int a, int b) {
    // count numbers with unique digits in the range [a, b] inclusive.
    // e.g., f([1..20]) = 19, where '11' has non-unique.
    // Prolly some mathy stuff
    // prefix sums. Can enumerate over all numbers. At most 4N, since a,b<=1000
    // Can we do better?
    return dp[b] - dp[a - 1];
  }
};
