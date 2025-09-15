#include <vector>

class Solution {
 public:
  int missingElement(std::vector<int>& nums, int k) {
    // Sorted ascending order, unique elements.
    // Return the kth missing number starting from the leftmost number of the
    // array.
    //
    // For the unsorted variant to find first missing positive, it relies on a
    // three-pass approach (just as a recap for myself):
    // 1. Mark out-of-bounds, i.e., negative or >n to a Sentinel value, e.g.,
    //    n+1.
    // 2. Iterate through again, marking the within-bounds integer's
    //    corresponding index, e.g., negative.
    // 3. Check first non-negative number. Return the corresponding index.
    //
    // For the given constraints, we only have positive elements.
    // An O(N) approach seem to be possible.
    // iterate through, maintaining a count variable. Start from 0 on the
    // leftmost, decrement it by the difference between this and the next number
    //
    // can we do better?
    // Seems Binary-Search will do fine. What's our feasibility condition?
    // The earlier count can be obtained from some function of curr and nums[0]
    // E.g., f(nums[1],nums[0]) = 7-4 - 1 = 2 missing numbers between 4 and 7
    //       f(nums[2],nums[0]) = 9-4 - 2 = 3 missing numbers.
    // Thus, f: idx -> nums[idx] - nums[0] - idx to get the number of missing
    // numbers between index 0 and idx.
    // Thus, if k <= f(idx), then our number is <= nums[idx], recurse left.
    // otherwise, recurse right.
    // Once we obtain idx, we take the k-f(idx) missing number from nums[idx].
    const auto n = static_cast<int>(nums.size());

    int left = 0;
    int right = n;
    while (left < right) {
      int mid = left + (right - left) / 2;
      auto missing = nums[mid] - nums[0] - mid;
      if (k <= missing) {
        right = mid;
      } else {
        left = mid + 1;
      }
    }
    // The range of numbers between nums[left-1] nums[left] has the kth
    // missing number.
    auto offset = nums[left - 1] - nums[0] - (left - 1);
    return nums[left - 1] + (k - offset);
  }
};
