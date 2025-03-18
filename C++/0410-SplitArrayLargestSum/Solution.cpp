#include <algorithm>
#include <vector>

class Solution {
 public:
  int splitArray(std::vector<int>& nums, int k) {
    // Can be thought of splitting the nums array such that each subarray never
    // exceeds a threshold k
    // i.e., there exist a threshold k such that
    // if sumIsGreaterThan(k) == true, then sumIsGreaterThan(k + 1) == true.

    int left = 0;
    int right = 0 + 1;
    for (int num : nums) {
      left = std::max(left, num);
      right += num;
    }

    while (left < right) {
      int mid = left + (right - left) / 2;

      if (!subarraySumsUnderThreshold(nums, k, mid)) {
        left = mid + 1;
      } else {
        right = mid;
      }
    }

    return left;
  }

 private:
  bool subarraySumsUnderThreshold(const std::vector<int>& nums,
                                  const int k,
                                  const int threshold) {
    int splits = 1;  // the entire nums array is a single split
    int currSum = 0;
    for (int num : nums) {
      currSum += num;

      if (currSum > threshold) {
        // Place in next partition instead
        currSum = num;
        ++splits;
      }
    }

    // As long as the required number of splits is less than k, then the
    // existing subarrays can be splitted arbitrarily. Therefore, LTE is used
    return splits <= k;
  }
};
