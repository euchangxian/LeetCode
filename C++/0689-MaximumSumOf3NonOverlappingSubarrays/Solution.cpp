#include <array>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  std::vector<int> maxSumOfThreeSubarrays(std::vector<int>& nums, int k) {
    // Hm. How do we reduce this problem? If k is 1, then the sum is the answer.
    // If 2, then exclude the minimum.
    // If 3, exclude the smallest two (depending on size of the array)
    // ...
    // Hm,
    // subarrays = ceil(nums.size / k)
    // excluded = nums.size % k
    // At first glance, feels like greedy would work. But notice that subarrays
    // must be of length == k, not <= k.
    // i.e., when we pick a starting element at i, the subarray [i..i+k) must be
    // considered.
    //
    // Constraints are kinda weird though.
    // 1 <= nums.length <= 2 * 10^4 (n^2 solution allowed)
    // but 1 <= k <= floor(nums.length / 3)
    // which are contradicting? constraint of k implies nums.length >= 3
    //
    // nums[i] < 2^16 = 65,356
    // Hm, why is nums[i] so small?
    //
    // Okay, but back to the problem. Seeing it as where to start/stop/partition
    // the array would work?
    // Naively:
    // solve(nums[1..n], k, 3) = max{
    //                          solve(nums[2..n], k, 3)
    //                          solve(nums[1+k..n], k, 2) + sum(nums[1..k])
    //                        }
    // (on a side note, looking k elements ahead is kinda uncomfortable to me)
    // Also, can forsee quite a lot of repeated work when calculating
    // sum(nums[i..i+k]). Can we preprocess?
    // Let A such that A[i] = sum(nums[i..i+k])?
    // or would A[i] = sum(nums[i-k..i]) be better? (start at i vs end at i)
    //
    // Okay, now suppose we have A.
    // We still have an O(2^n) solution (2 choices at each i)
    // Top-down:
    // Base case when 3 subarrays have been picked. Prune if no way to pick
    // remaining x subarrays with the subarray nums[i..n].
    // Memoize? Prolly a 2-state, (i, x), which is technically O(3n) space.
    // i.e., max sums of x subarrays of the first i elements, x <= 3
    // memo[i][x] = max{
    //                  memo[i-1][x],
    //                  memo[i-k+1][x-1] + A[i] // A[i] is sum ending at i
    //                 } (this is the recurrence for bottom-up, actually)
    //
    // We also need to memorize i... Rough. Not entirely sure how.
    const int n = static_cast<int>(nums.size());

    // Easier to reason about indices than with windowSums.
    std::vector prefixSum(n + 1, 0);
    for (int i = 0; i < n; ++i) {
      prefixSum[i + 1] += prefixSum[i] + nums[i];
    }

    // dp[i][x] = dp[i-1][x] + dp[i-k+1][x-1]
    std::vector<std::array<int, 4>> dp(n + 1, std::array<int, 4>{});

    // for path reconstruction
    std::vector<std::array<int, 4>> choices(n + 1, std::array<int, 4>{});
    for (int x = 1; x <= 3; ++x) {
      // for each i: (exclusive end)
      for (int i = k * x; i <= n; ++i) {
        // skip
        dp[i][x] = dp[i - 1][x];
        choices[i][x] = choices[i - 1][x];

        // take current subarray
        int takeSum = dp[i - k][x - 1] + prefixSum[i] - prefixSum[i - k];
        if (takeSum > dp[i][x]) {
          dp[i][x] = takeSum;
          choices[i][x] = i - k;  // record where this subarray starts
        }
      }
    }

    std::vector<int> result(3);
    int i = n;
    for (int x = 3; x >= 1; --x) {
      int idx = choices[i][x];
      result[x - 1] = idx;
      i = idx;
    }

    return result;
  }
};
