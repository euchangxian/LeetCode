#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  long long countFairPairs(std::vector<int>& nums, int lower, int upper) {
    // A pair (i, j) is fair if:
    // 0 <= i < j < n i.e., i, j is distinct and
    // lower <= nums[i] + nums[j] <= upper i.e., the sum is within the range.
    // Sort and count using two pointer?
    // if sum is smaller than lower => move left pointer forward
    // if sum is greater than upper => move right pointer backward.
    // if sum is within range?
    // Not straightfoward.
    // Sort and binary search the lower and upper bound. Count the number of
    // elements within.
    // i.e., with an element x, we want to find y such that
    // x + y >= lower and
    // x + y <= greater
    // Rewriting, we have y >= lower - x and y <= greater - x
    // for y >= lower - x, std::lower_bound(lower-x)
    // for y <= greater - x, std::prev(std::upper_bound(greater-x))
    // O(nlogn)
    //
    // To do better, go back to the two pointer one.
    // Reduce the problem!
    // First, count the number of pairs where x + y <= upper -> x + y < upper+1
    // Then, count the number of pairs where x + y < lower.

    std::sort(nums.begin(), nums.end());

    // long long count = 0LL;
    // for (int i = 0; i < nums.size(); ++i) {
    //   // NOTE: search starting from nums.begin() + i + 1, instead of the
    //   whole
    //   // array. Handles distinct-ness cleanly.
    //   auto lb =
    //       std::lower_bound(nums.begin() + i + 1, nums.end(), lower -
    //       nums[i]);
    //   auto ub =
    //       std::upper_bound(nums.begin() + i + 1, nums.end(), upper -
    //       nums[i]);
    //
    //   count += ub - lb;
    // }
    // return count;

    return countPairsLessThan(nums, upper + 1) -
           countPairsLessThan(nums, lower);
  }

 private:
  // - If sum < target: all pairs with left fixed and right moving leftward are
  //   valid
  // - If sum >= target: need to try a smaller right value
  long long countPairsLessThan(std::vector<int>& nums, int limit) {
    long long count = 0LL;
    int l = 0;
    int r = static_cast<int>(nums.size()) - 1;

    while (l < r) {
      int sum = nums[l] + nums[r];
      if (sum < limit) {
        count += r - l;
        ++l;
      } else {
        --r;
      }
    }
    return count;
  }
};
