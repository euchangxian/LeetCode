#include <algorithm>
#include <utility>
#include <vector>

class Solution {
 public:
  int maxJumps(std::vector<int>& arr, int d) {
    // In one step, jump from index i to index:
    // - i+x: i+x < n and 0<x<=d
    // - i-x: i-x >=0 and 0<x<=d
    // Additionally,
    // jump from index i to index j if:
    // - arr[i] > arr[j] and arr[i] > arr[k] for all min(i,j) < k < max(i,j)
    // Choose any start index, return the maximum number of indices that can be
    // visited.
    //
    // Only jump from index i to index j IF |i-j|<=d, and every arr[k] between
    // i and j (j inclusive) is < nums[i].
    // How do we pick an optimal start index?
    //
    // Most-likely thinking in-reverse is better.
    // Feels like Topological Sorting in some way.
    // Start from the smallest value? Having to search back and forth d indices
    // is expensive though.
    // Sort (arr[i], i)?
    // Let the transformed indices be t.
    // Jump from t to t+1 if arr[t_val] < arr[t+1_val] and t_idx - t+1_idx <= d.
    // Then, dp[t] = max{dp[t-k]} + 1.
    // O(d^2)?.
    const auto n = static_cast<int>(arr.size());
    std::vector<std::pair<int, int>> sorted;
    sorted.reserve(n);
    for (auto i = 0; i < n; ++i) {
      sorted.emplace_back(arr[i], i);
    }
    std::ranges::sort(sorted);

    auto result = 0;
    std::vector<int> dp(n, 1);  // each index visits at least itself.
    for (const auto [_, i] : sorted) {
      // scan right of idxI until blocked by a cell >= arr[i]
      for (auto j = i + 1; j < n && j <= i + d && arr[j] < arr[i]; ++j) {
        dp[i] = std::max(dp[i], dp[j] + 1);
      }

      // scan left of idxI until blocked
      for (auto j = i - 1; j >= 0 && j >= i - d && arr[j] < arr[i]; --j) {
        dp[i] = std::max(dp[i], dp[j] + 1);
      }
      result = std::max(result, dp[i]);
    }
    return result;
  }
};
