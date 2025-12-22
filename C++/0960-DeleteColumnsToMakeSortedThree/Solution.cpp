#include <algorithm>
#include <string>
#include <vector>

class Solution {
 public:
  int minDeletionSize(std::vector<std::string>& strs) {
    // n strings of same length.
    // Choose any deletion indices, delete all characters in those indices for
    // each string.
    // Delete indices such that the final array has every string in
    // lexicographic order (each string is sorted).
    // Return the minimum number of indices to achieve that.
    //
    // Max answer is k-1, where k is the length of the string.
    // Feels like Binary Search, but we can't arbitrarily delete any indices.
    // Every string must delete the same indices.
    // Longest Increasing Subsequence-like.
    const auto n = static_cast<int>(strs.size());
    const auto m = static_cast<int>(strs[0].size());

    // dp[i] is the longest subsequence ending with the ith element.
    // for all i < j, if A[k][i] < A[k][j], then
    // dp[j] = max{dp[j], dp[i] + 1}
    std::vector<int> dp(m, 1);

    int result = m - 1;
    int k = 0;
    for (int j = 0; j < m; ++j) {
      for (int i = 0; i < j; ++i) {
        for (k = 0; k < n; ++k) {
          if (strs[k][i] > strs[k][j]) {
            break;
          }
        }

        if (k == n && dp[i] + 1 > dp[j]) {
          dp[j] = dp[i] + 1;
        }
        result = std::min(result, m - dp[j]);
      }
    }
    return result;
  }
};
