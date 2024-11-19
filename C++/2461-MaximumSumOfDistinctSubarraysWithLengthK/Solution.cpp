#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <unordered_map>
#include <vector>

class Solution {
 public:
  long long maximumSubarraySum(std::vector<int>& nums, int k) {
    // fixed sized sliding window of size k with an extra constraint where
    // we want unique elements only.
    std::unordered_map<int, int> frequency;

    long long maxSum = 0LL;
    long long windowSum = 0LL;
    for (int i = 0; i < nums.size(); ++i) {
      if (i >= k) {
        // decrement left-most
        windowSum -= nums[i - k];
        if (--frequency[nums[i - k]] == 0) {
          frequency.erase(nums[i - k]);
        }
      }

      // add right most
      ++frequency[nums[i]];
      windowSum += nums[i];
      if (i >= k - 1 && frequency.size() == k) {
        maxSum = std::max(maxSum, windowSum);
      }
    }
    return maxSum;
  }
};
