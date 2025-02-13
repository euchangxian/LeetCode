#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  int maxCoinsMemo(std::vector<int>& nums) {
    // Burst ith balloon, get nums[i-1] * nums[i] * nums[i+1] coins.
    // Balloons out of bounds are treated as 1 coin.
    // Maximum coins.
    //
    // Naively, DFS + backtracking.
    // i.e., try popping at each index. Bounds need to be adjusted carefully.
    // func dfs(nums):
    //   sum := 0
    //   for i in [0..n-1]:
    //     score := nums[i-1] * nums[i] * nums[i+1]
    //     sum = max(sum,
    //               score + dfs(nums[0..i-1]) + dfs(nums[i+1..n-1])))
    //   return sum
    //
    // O(n * n!).
    // Where repeated work??
    // We are computing the optimal split i.e., the optimal balloon to pop at
    // each level, such that the root-to-leaf path gives the maximum coin.
    // Note that by popping nums[i], nums[i-1] and nums[i+1] become neighbours.
    // Implementation is definitely not trivial.
    // Memoization is difficult too, since we need to keep track of the
    // balloon(s) popped, memo[l][r] is not sufficient.
    //
    // How can we do better? Try a reverse perspective? i.e., time travelling.
    // What if we were to build up?
    //
    // func dfs(nums, left, right):
    //   sum := 0
    //   for i in [left+1..right-1]:                       // exclusive
    //     score := nums[left] * nums[i] * nums[right]     // do bounds check
    //     sub := dfs(nums, left, i) + dfs(nums, i, right) // inclusive i
    //     sum = max(sum, score + sub)
    //   return sum
    //
    // NOTE:
    // score := nums[left] * nums[i] * nums[right] and
    // sub := dfs(nums, left, i) + dfs(nums, i, right)
    // Given that we are working in reverse, each choice indicates the
    // optimal "last" balloon to be popped in the range.
    // Thus, when adding a balloon, we need to keep track of it through the
    // `left` and `right` variables, allowing future neighbouring pops to
    // account for this balloon.
    //
    // Overall, implementation with the "last" balloon to be popped is simpler.
    // How can we do better?
    // Memoization? Which states are necessary? Definitely (left, right).
    // What does memo[l][r] represent then?
    // memo[l][r] represents the maximum coin obtainable from the range of
    // balloons (l, r).
    // Thus, we have the following:
    // - memo[l][r] = nums[l] (or nums[r]) for all l == r
    // - memo[l][r] = 0 for all l > r
    // - memo[l][r] = max(memo[l][r],
    //                    memo[l][i] + memo[i][r] + pop(i)) for all i in [l..r]
    // O(N^3), O(N^2) subproblems, O(N) time to solve each subproblem.
    //
    // Can we do bottom up?
    // Base case are same. Notice that we only need the upper triangular matrix.
    // Diagonals (i, i) are thus equal to nums[i].
    //
    // What are the transitions given dp[l][r]?
    // Given the shape of the required matrix, hm.
    const int n = nums.size();

    // pad. Effectively 1-index nums.
    std::vector<int> balloons(n + 2);
    balloons.front() = 1, balloons.back() = 1;
    for (int i = 1; i <= n; ++i) {
      balloons[i] = nums[i - 1];
    }

    std::vector<std::vector<int>> memo(n + 2, std::vector<int>(n + 2, -1));
    dfs(balloons, memo, 0, n + 1);
    return memo[0][n + 1];
  }

  int maxCoins(std::vector<int>& nums) {
    // For bottom-up, notice that to compute larger ranges e.g.,
    // dp[left][right], we need:
    // - dp[left][i]   // smaller left range
    // - dp[i][right]  // smaller right range
    // Thus, we can compute ranges of smaller lengths, iteratively.
    constexpr int MAX_N = 300;
    const int n = nums.size();

    std::array<int, MAX_N + 2> balloons;
    balloons[0] = 1, balloons[n + 1] = 1;
    std::copy(nums.begin(), nums.end(), balloons.begin() + 1);

    // implicit base cases already initialized:
    // dp[i][i] = 0 (range of length 0)
    std::array<std::array<int, MAX_N + 2>, MAX_N + 2> dp{};

    // k represents the distance between left and right. i.e,. length + 1
    for (int k = 2; k < n + 2; ++k) {
      for (int left = 0; left < n + 2 - k; ++left) {
        int right = left + k;
        for (int i = left + 1; i < right; ++i) {
          int score = balloons[left] * balloons[i] * balloons[right];
          dp[left][right] =
              std::max(dp[left][right], score + dp[left][i] + dp[i][right]);
        }
      }
    }

    return dp[0][n + 1];
  }

 private:
  int dfs(const std::vector<int>& balloons,
          std::vector<std::vector<int>>& memo,
          const int left,
          const int right) const {
    if (left > right) {
      return 0;
    }
    if (left == right) {
      return balloons[left];
    }
    if (memo[left][right] != -1) {
      return memo[left][right];
    }

    int best = 0;
    // exclusive range, (left, right)
    for (int i = left + 1; i < right; ++i) {
      int score = balloons[left] * balloons[i] * balloons[right];
      best = std::max(best, score + dfs(balloons, memo, left, i) +
                                dfs(balloons, memo, i, right));
    }

    return memo[left][right] = best;
  }
};
