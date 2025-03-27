#include <algorithm>
#include <array>
#include <utility>
#include <vector>

constexpr int MAX_N = 500;
constexpr int MAX_NUM = 2000;
class Solution {
 public:
  int maxUncrossedLines(std::vector<int>& nums1, std::vector<int>& nums2) {
    // Draw lines such that nums1[i] <--> nums2[j] if num1[i] == nums2[j].
    // Return maximum number of lines that can be drawn such that no two
    // lines intersect.
    //
    // Wow... can be reduced into Longest Common Subsequence.
    const int m = nums1.size();
    const int n = nums2.size();

    // after the ith iteration, dp[j] represents dp[i][j], which is the length
    // of the longest common subsequence of nums1[..i] and nums2[..j]
    std::array<int, MAX_N + 1> dp{};
    for (int i = 1; i <= m; ++i) {
      std::array<int, MAX_N + 1> curr{};
      for (int j = 1; j <= n; ++j) {
        if (nums1[i - 1] == nums2[j - 1]) {
          curr[j] = dp[j - 1] + 1;
        } else {
          curr[j] = std::max(curr[j - 1], dp[j]);
        }
      }
      dp = std::move(curr);
    }

    return dp[n];
  }
};
