#include <algorithm>
#include <array>
#include <ranges>
#include <vector>

constexpr int MAX_NK = 1E3;
class Solution {
 public:
  int maximumLength(std::vector<int>& nums, int k) {
    // Given nums and positive integer k.
    // Subsequence sub of length x is valid if:
    // (sub[0]+sub[1])%k == (sub[1]+sub[2])%k == ... == (sub[x-2]+sub[x-1])%k
    // Return the longest valid subsequence.
    //
    // Valid if the k-mod-sum of every adjacent element in the subsequence is
    // equal.
    // n <= 1E3 = 1000. Pretty small, something like an n^2 logn solution.
    //
    // The mod-sum can only take k possible values.
    // Thus, we can form dp[i] = maximum length of a subsequence ending at x,
    // such that x % k == i.
    //
    // Hm. Not exactly complete. Also, another observation:
    // if (a+b)%k == (b+c)%k, then a%k == c%k, i.e., alternating values in the
    // subsequence are congruent-mod k.
    //
    // Transform nums into the modulo residual array, where each element x
    // is modulo-k.
    // dp[i][j] represents the length of the longest valid subsequence ending
    // at the current index, where i = x % k, and j is the previous modulo
    // residue y % k in the subsequence.
    // Notice the alternating property is captured in the transition:
    // dp[i][j] = dp[j][i] + 1
    int result = 0;

    std::array<std::array<int, MAX_NK>, MAX_NK> dp{};
    for (auto i : nums | std::views::transform([k](auto x) { return x % k; })) {
      for (int j = 0; j < k; ++j) {
        dp[i][j] = dp[j][i] + 1;
        result = std::max(result, dp[i][j]);
      }
    }
    return result;
  }
};
