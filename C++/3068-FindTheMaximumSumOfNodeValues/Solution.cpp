#include <array>
#include <limits>
#include <vector>

constexpr int MAX_N = 2E4;
using i64 = long long;
class Solution {
 public:
  i64 maximumValueSum(std::vector<int>& nums,
                      int k,
                      std::vector<std::vector<int>>& edges) {
    // Given a tree, and n nodes numbered 0 to n-1,
    // edges[i] = [u, v] indicate a bidirectional edge between nodes u and v.
    // Choose any edge (u, v) and update the values:
    // - nums[u] = nums[u] XOR k
    // - nums[v] = nums[v] XOR k
    // Return maximum sum, performing the operations any number of times.
    //
    // Note that if we have node u connected to two children, performing the
    // operations on u twice will result in net 0 change to the value of u.
    // With this, a node can be in one of two states:
    // - nums[u] = nums[u]
    // - nums[u] = nums[u] ^ k
    //
    // Hm. Naively, 2^(n-1), each edge has two choices: pick/skip.
    //
    // Hm. We do not consider edges. Because we can "toggle" the state of each
    // node using any number of operations.
    const int n = nums.size();
    std::array<std::array<i64, 2>, MAX_N + 1> dp{};
    dp[0][0] = 0;
    dp[0][1] = std::numeric_limits<i64>::min();

    for (int i = 1; i <= n; ++i) {
      int x = nums[i - 1];
      dp[i][0] = std::max(x + dp[i - 1][0], (x ^ k) + dp[i - 1][1]);
      dp[i][1] = std::max(x + dp[i - 1][1], (x ^ k) + dp[i - 1][0]);
    }
    return dp[n][0];
  }
};
