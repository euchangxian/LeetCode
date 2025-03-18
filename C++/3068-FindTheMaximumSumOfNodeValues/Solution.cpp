#include <climits>
#include <vector>

// There exists an undirected tree with n nodes numbered 0 to n - 1. You are
// given a 0-indexed 2D integer array edges of length n - 1, where edges[i] =
// [ui, vi] indicates that there is an edge between nodes ui and vi in the tree.
// You are also given a positive integer k, and a 0-indexed array of
// non-negative integers nums of length n, where nums[i] represents the value of
// the node numbered i.
//
// Alice wants the sum of values of tree nodes to be maximum, for which Alice
// can perform the following operation any number of times (including zero) on
// the tree:
//
// Choose any edge [u, v] connecting the nodes u and v, and update their values
// as follows: nums[u] = nums[u] XOR k nums[v] = nums[v] XOR k Return the
// maximum possible sum of the values Alice can achieve by performing the
// operation any number of times.
class Solution {
 public:
  long long maximumValueSum(std::vector<int>& nums,
                            int k,
                            std::vector<std::vector<int>>& edges) {
    using ll = long long;
    int n = nums.size();
    std::vector<std::vector<ll>> dp =
        std::vector<std::vector<ll>>(2, std::vector<ll>(n + 1, 0));

    dp[0][0] = 0;
    dp[1][0] = LLONG_MIN;

    for (int i = 1; i < n + 1; ++i) {
      int x = nums[i - 1];

      dp[0][i] = std::max(x + dp[0][i - 1], (x ^ k) + dp[1][i - 1]);
      dp[1][i] = std::max(x + dp[1][i - 1], (x ^ k) + dp[0][i - 1]);
    }
    return dp[0][n];
  }
};
