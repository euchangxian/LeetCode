#include <algorithm>
#include <array>
#include <vector>

constexpr int MAX_N = 1000;
class Solution {
 public:
  std::vector<int> largestDivisibleSubset(std::vector<int>& nums) {
    // Distinct positive integers. Return the largest subset of nums, such that
    // every pair (answer[i], answer[j]) in this subset satisfies:
    // - answer[i] % answer[j] == 0, or
    // - answer[j] % answer[i] == 0
    // i.e., divisible or a multiple of each other.
    //
    // Naively, insert all into a HashSet. Then, for in ascending order of
    // nums[i], check each nums[j] > nums[i] for nums[j] % nums[i] == 0.
    // O(N^2).
    // Inefficient at some point, e.g., nums={2, 4, 8}, can stop at nums[0] = 2.
    // How can we do better?
    //
    // Is the uniqueness a property we can exploit?
    // What about maintaining an array of divisible subsets.
    // Then, to check if nums[j] can be inserted into a subset, we can check
    // the largest element of each subset, whether it divides nums[j].
    //
    // Ah. No...
    // E.g., nums = {3, 6, 15, 45}
    // this will naively determine {3, 6}, and {15, 45}, instead of {3, 15, 45}.
    // Need to do something like Longest Increasing Subsequence, with
    // backtracking to return the solution.
    // Then, to add nums[j] to an existing subsequence, nums[j] % nums[i] == 0
    // Not patience solitaire.
    const int n = nums.size();
    std::sort(nums.begin(), nums.end());

    int largestSize = 1;
    int idx = 0;

    std::array<int, MAX_N> dp;
    std::array<int, MAX_N> parent;
    std::memset(parent.data(), -1, sizeof(parent));
    for (int i = 0; i < n; ++i) {
      dp[i] = 1;
      for (int j = 0; j < i; ++j) {
        if (nums[i] % nums[j] == 0 && dp[j] + 1 > dp[i]) {
          dp[i] = dp[j] + 1;  // extend
          parent[i] = j;

          if (dp[i] > largestSize) {
            largestSize = dp[i];
            idx = i;
          }
        }
      }
    }

    std::vector<int> answer;
    answer.reserve(largestSize);
    for (int i = idx; i != -1; i = parent[i]) {
      answer.push_back(nums[i]);
    }

    // NOTE: No need to reverse. We just want a subset.
    return answer;
  }
};
