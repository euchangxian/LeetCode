#include <deque>
#include <vector>

using i64 = long long;
constexpr int MOD = 1E9 + 7;

class Solution {
 public:
  int countPartitions(std::vector<int>& nums, int k) {
    // partition nums into non-empty contiguous segments such that in each
    // segment, the difference between the max and min elements is at most k.
    // Return the number of ways to partition modulo 1E9+7.
    //
    // Hm.
    // For each partition, while diff(min, max) <= k, we can add the next
    // element into the partition, or the next partition.
    // Seems like Sliding Window.
    // Ah. But we cant determine if a min/max is still in the subarray
    // considered.
    // Need a Deque?
    // Sliding window min/max?
    //
    // How do we count then?
    const auto n = static_cast<int>(nums.size());

    // number of ways to partition first i elements.
    // dp[i] = sum(dp[0..j]) for 0 <= j <= i-1
    // - such that max(nums[j..i-1]) - mins(nums[j..i-1]) <= k
    std::vector<int> dp(n + 1);
    dp[0] = 1;

    i64 acc = 1;
    std::deque<int> windowMax;
    std::deque<int> windowMin;
    for (int l = 0, r = 0; r < n; ++r) {
      while (!windowMax.empty() && nums[r] > nums[windowMax.back()]) {
        windowMax.pop_back();
      }
      windowMax.push_back(r);

      while (!windowMin.empty() && nums[r] < nums[windowMin.back()]) {
        windowMin.pop_back();
      }
      windowMin.push_back(r);

      while (nums[windowMax.front()] - nums[windowMin.front()] > k) {
        acc = (acc - dp[l++] + MOD) % MOD;

        if (windowMin.front() < l) {
          windowMin.pop_front();
        }
        if (windowMax.front() < l) {
          windowMax.pop_front();
        }
      }
      dp[r + 1] = acc;
      acc = (acc + dp[r + 1]) % MOD;
    }
    return dp[n];
  }
};
