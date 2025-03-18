#include <algorithm>
#include <vector>

class Solution {
 public:
  int maxProduct(std::vector<int>& nums) {
    int n = nums.size();

    int maxProd = nums[0];
    int minSoFar = maxProd;
    int maxSoFar = maxProd;

    // Similar to Kadane's Algorithm:
    // At each step, there are two decisions:
    // 1. Extend the previous subarray, or
    // 2. Start a new subarray
    //
    // Although the product of the previous subarray may be negative,
    // there is a possibility that nums[i] is also negative, resulting in a
    // large product.
    for (int i = 1; i < n; ++i) {
      if (nums[i] < 0) {
        // if the current number is negative, then maxSoFar * nums[i] would
        // actually result in a negative number (if maxSoFar is positive).
        // Swapping allows us to cleanly retain the max and min semantics
        // below.
        std::swap(minSoFar, maxSoFar);
      }

      minSoFar = std::min(nums[i], minSoFar * nums[i]);
      maxSoFar = std::max(nums[i], maxSoFar * nums[i]);

      maxProd = std::max(maxProd, maxSoFar);
    }

    return maxProd;
  }
};
