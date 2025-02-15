#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdlib>
#include <utility>

constexpr int MAX_N = 1000;

constexpr std::pair<std::array<int, 7>, int> toDigits(int n) {
  std::array<int, 7> result{};
  int i = 0;
  while (n) {
    result[i++] = (n % 10);
    n /= 10;
  }

  std::reverse(result.begin(), result.begin() + i);
  return {result, i};
}

constexpr bool canPartition(const int target,
                            const std::array<int, 7>& digits,
                            const int length,
                            int currSum,
                            int idx) {
  // Complete Search
  // Worst case 2^7 * 1000 ~= 10^5
  if (idx >= length || currSum > target) {
    return currSum == target;
  }

  int val = 0;

  // try expanding this substring
  for (int i = idx; i < length; ++i) {
    val = val * 10 + digits[i];
    if (canPartition(target, digits, length, currSum + val, i + 1)) {
      return true;
    }
  }
  return false;
}

constexpr std::array<int, MAX_N + 1> dp = []() {
  std::array<int, MAX_N + 1> dp{};
  for (int i = 1; i <= MAX_N; ++i) {
    int square = i * i;
    auto [digits, length] = toDigits(square);
    dp[i] = dp[i - 1];
    if (canPartition(i, digits, length, 0, 0)) {
      dp[i] += square;
    }
  }
  return dp;
}();

class Solution {
 public:
  int punishmentNumber(int n) {
    // Punishment Number is defined as the sum of the squares of all integers
    // i in [1..n] such that the decimal representation of  (i * i) can be
    // partitioned into contiguous substrings such that the sum of the integer
    // values of these substrings equals i.
    // Confusing, but e.g., n = 10, punishment number = 182
    // - 1 in [1..10], 1 * 1 = 1, "1" can be partitioned into 1 == i.
    // - 9, 9*9 = 81, partitioned into "8" and "1" such that 8+1 == 9
    // - 10, 10*10=100, partitioned into "10" and "0" such that 10+0 == 10
    //
    // Feels like DP. n <= 1000. The less trivial part is finding the
    // partitions, since the decimal representation can be partioned
    // arbitrarily. Though, small constraints.
    // Not trivial to precompute in compile time though, given that std::string
    // is not constexpr.
    return dp[n];
  }
};
