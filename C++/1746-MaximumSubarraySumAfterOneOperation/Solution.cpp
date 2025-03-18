#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  int maxSumAfterOperation(std::vector<int>& nums) {
    // Exactly one operation where nums[i] can be replaced with its square,
    // nums[i] = nums[i] * nums[i].
    // Return max possible subarray sum.
    // Hmmm. Complexity lies in nums[i] < 0.
    // Either: nums[i] > 0 such that nums[i] * nums[i] causes the sum to be big.
    // or very big nums[i] < 0
    // Sliding window? Hard to slide.
    // Naively, try squaring every nums[i], and taking the max subarray sum
    // using a sliding window. O(n^2)
    // How can we do better? Is there any kind of heuristics we can use to
    // choose which nums[i] to square.
    // Ohh. Recall Kadane's. Suppose we want to solve a simpler variant of this
    // problem, without squaring. Then the subproblems would be simple:
    // maxSubarraySum[i] = max{
    //   nums[i],                       // the prev sums could be negative
    //   maxSubarraySum[i-1] + nums[i],
    // }
    // Now, we can extend it slightly, such that we have maxSum[i][hasOperation]
    // maxSum[i][false] = max{
    //   maxSum[i-1][false] + nums[i],
    //   nums[i]
    // }
    // maxSum[i][true] max{
    //   maxSum[i-1][false] + (nums[i]*nums[i]),
    //   maxSum[i-1][true] + nums[i],
    //   nums[i] * nums[i]
    // }
    // i.e., maxSum[i][hasOp] is the maximum sum of the subarray including i.
    // Quite nice to think of it as State Transitions.
    std::vector<std::array<int, 2>> dp(nums.size(), std::array<int, 2>{});
    dp[0][false] = nums[0];
    dp[0][true] = nums[0] * nums[0];

    int maxSum = std::max(dp[0][false], dp[0][true]);
    for (int i = 1; i < nums.size(); ++i) {
      dp[i][false] = std::max(nums[i], dp[i - 1][false] + nums[i]);
      dp[i][true] = std::max({nums[i] * nums[i], dp[i - 1][true] + nums[i],
                              dp[i - 1][false] + (nums[i] * nums[i])});

      maxSum = std::max({maxSum, dp[i][false], dp[i][true]});
    }

    return maxSum;
  }
};
