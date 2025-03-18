#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  int smallestDivisor(std::vector<int>& nums, int threshold) {
    // choose a positive integer divisor, divide all elements by it, and sum
    // the result.
    // Find the smallest divisor such that result above is less than or equal
    // to the threshold.
    //
    // The larger the divisor, the smaller the sum. Therefore, there is a point
    // k where sum / k <= threshold, sum / k + 1 > threshold.
    // Though, the division operation a ceiling division; the result is rounded
    // UP, regardless of how far it is. i.e., 1/4 == 0.25 ~= 1
    // i.e., 1 / 4 == 1
    //
    // montonic property looks like F, F, F, F, T, T
    //                                          ^ we want this
    // we want to find the upper-bound. Involves ceiling division and such.
    int left = 1;
    int right = *std::max_element(nums.begin(), nums.end());

    while (left < right) {
      int mid = left + (right - left) / 2;

      // if for the given divisor, sum <= threshold, then the minimum divisor
      // lies to the LEFT, and the sum can be decreased further, i.e., shrink
      // the the right search range.
      if (!feasible(nums, threshold, mid)) {
        // condition inverted just to keep the left->right ordering.
        left = mid + 1;
      } else {
        right = mid;
      }
    }
    return left;
  }

 private:
  bool feasible(std::vector<int>& nums, int threshold, int divisor) {
    int sum = 0;
    for (int num : nums) {
      // ceiling division
      sum += (num + divisor - 1) / divisor;
    }

    return sum <= threshold;
  }
};
