#include <algorithm>
#include <array>
#include <utility>
#include <vector>

constexpr int MAX_N = 500;
class Solution {
 public:
  int maxDotProduct(std::vector<int>& nums1, std::vector<int>& nums2) {
    // Return the maximum dot product between non-empty subsequences of nums1
    // and nums2.
    //
    // -1000 <= nums1[i],nums2[i] <= 1000 (can be negative)
    // DP[i][j]
    const auto m = static_cast<int>(nums1.size());
    const auto n = static_cast<int>(nums2.size());

    auto [min1, max1] = std::ranges::minmax(nums1);
    auto [min2, max2] = std::ranges::minmax(nums2);
    // take least negative.
    if (min1 > 0 && max2 < 0) {
      return min1 * max2;
    }
    if (max1 < 0 && min2 > 0) {
      return max1 * min2;
    }

    std::array<int, MAX_N + 1> dp;
    dp[n] = 0;

    std::array<int, MAX_N + 1> curr;
    for (int i = m - 1; i >= 0; --i) {
      for (int j = n - 1; j >= 0; --j) {
        auto take = (nums1[i] * nums2[j]) + dp[j + 1];
        auto skip1 = dp[j];
        auto skip2 = curr[j + 1];
        curr[j] = std::max({take, skip1, skip2});
      }
      dp = std::move(curr);
    }
    return dp[0];
  }

  int maxDotProductTLE(std::vector<int>& nums1, std::vector<int>& nums2) {
    // Return the maximum dot product between non-empty subsequences of nums1
    // and nums2.
    //
    // -1000 <= nums1[i],nums2[i] <= 1000 (can be negative)
    // DP[i][j]
    const auto m = static_cast<int>(nums1.size());
    const auto n = static_cast<int>(nums2.size());

    auto [min1, max1] = std::ranges::minmax(nums1);
    auto [min2, max2] = std::ranges::minmax(nums2);
    // take least negative.
    if (min1 > 0 && max2 < 0) {
      return min1 * max2;
    }
    if (max1 < 0 && min2 > 0) {
      return max1 * min2;
    }

    std::array<std::array<int, MAX_N + 1>, MAX_N + 1> memo{};
    auto dfs = [&](this auto&& dfs, int i, int j) {
      if (i >= m || j >= n) {
        // NOTE: this is unable to handle the edge-case where the maximum dot
        // product is < 0, but we need a non-empty subsequence.
        return 0;
      }

      auto& ans = memo[i][j];
      if (ans != 0) {
        return ans;
      }

      auto skip1 = dfs(i + 1, j);
      auto skip2 = dfs(i, j + 1);
      auto take = (nums1[i] * nums2[j]) + dfs(i + 1, j + 1);
      return ans = std::max({skip1, skip2, take});
    };

    return dfs(0, 0);
  }
};
