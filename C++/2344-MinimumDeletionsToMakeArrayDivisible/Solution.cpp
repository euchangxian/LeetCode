#include <algorithm>
#include <limits>
#include <numeric>
#include <vector>

class Solution {
 public:
  int minOperations(std::vector<int>& nums, std::vector<int>& numsDivide) {
    // Minimum number of deletions from nums, such that min(nums) divides all
    // elements in numsDivide.
    // GCD, then look for GCD % nums[i] == 0?
    // Also, trivial if there is a '1'.
    // Can avoid sorting. Two passes. Find the smallest element x that divides
    // the GCD.
    // Then count number of elements smaller than x
    int gcd = numsDivide[0];
    for (int i = 1; i < numsDivide.size(); ++i) {
      gcd = std::gcd(gcd, numsDivide[i]);
    }

    int smallestFactor = std::numeric_limits<int>::max();
    for (int i = 0; i < nums.size(); ++i) {
      if (nums[i] > gcd) {
        continue;
      }

      if (gcd % nums[i] == 0 && nums[i] < smallestFactor) {
        smallestFactor = nums[i];
      }
    }

    if (smallestFactor == std::numeric_limits<int>::max()) {
      return -1;
    }

    return std::count_if(nums.begin(), nums.end(), [smallestFactor](int x) {
      return x < smallestFactor;
    });
  }
};
