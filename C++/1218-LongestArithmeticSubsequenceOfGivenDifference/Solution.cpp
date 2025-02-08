#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdlib>
#include <ranges>
#include <vector>

class Solution {
 public:
  int longestSubsequence(std::vector<int>& arr, int difference) {
    // Return length of longest subsequence in arr which is an arithmetic
    // sequence such that adjacent elements differ exactly by diff.
    // LIS, a little more constrained.
    // Not so straightforward to replace the LIS (patience solitaire)
    // Similar problem statement to 2407-Longest Increasing Subsequence Two,
    // where we need to find the LIS where the difference is at most K.
    // Solved by using Range Maximum Queries on a Segment Tree indexed by
    // values to determine the LIS to extend from.
    //
    // However, we do not need Range Queries here, since the difference K is
    // a fixed integer.
    // Let dp[val] represent the LIS ending at val. Then,
    // dp[val] = dp[val - diff] + 1;
    //
    // Fun comparisons between the LIS variants.

    // -2*10e4 <= x <= 2*10e4
    constexpr int SHIFT = 20'000;
    std::array<int, SHIFT * 2 + 1> dp{};
    auto shifted = arr | std::ranges::views::transform(
                             [](int x) -> int { return x + SHIFT; });
    dp[*shifted.begin()] = 1;

    int lis = 1;
    for (int x : shifted | std::ranges::views::drop(1)) {
      dp[x] = dp[std::max(0, x - difference)] + 1;
      lis = std::max(lis, dp[x]);
    }
    return lis;
  }
};
