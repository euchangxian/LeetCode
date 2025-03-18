#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  int minimumSize(std::vector<int>& nums, int maxOperations) {
    // Splitting as evenly as possible, i.e, greedy approach does NOT work.
    // Consider nums = {9}, maxOperations = 2
    // split 9 into {4, 5}
    // split 5 into {4, 3, 2}
    // max = 4
    // V.S.
    // split 9 into {6, 3}
    // split 6 into {3, 3, 3}
    // max = 3
    //
    // But we do want to split the largest element though.
    // NOTE: Kinda already knew it was Binary Search though. But the
    // monotonicity does not really seem obvious at all. Essentially, the
    // smaller the maximum value, the more operations is used.
    // We want to find the minimum maxValue such that the number of operations
    // is still <= maxOperations.
    // e.g., for nums = {14}, if we want maxValue = 3, the resulting split which
    // has k elements, has a sum == 14, i.e,. k * split[i] == 14.
    // Simplifying, k * maxValue >= 14 --> k >= 14/maxValue
    // where k is the number of elements needed!
    // We can find an lower bound on k with ceiling(14/maxValue), which would
    // also give us the number of operations necessary, with ops = k-1

    int left = 1;  // min value is 1
    int right = *std::max_element(nums.begin(), nums.end());

    while (left < right) {
      int mid = left + (right - left) / 2;

      // if current max can be achieved, then the minimum maxValue lies to the
      // left, i.e., is smaller. Thus, shrink the right range
      if (feasible(nums, maxOperations, mid)) {
        right = mid;
      } else {
        left = mid + 1;
      }
    }
    return left;
  }

 private:
  bool feasible(std::vector<int>& nums, int maxOperations, int maxValue) {
    int k = 0;

    for (int num : nums) {
      k += ((num + maxValue - 1) / maxValue) - 1;
    }
    return k <= maxOperations;
  }
};
