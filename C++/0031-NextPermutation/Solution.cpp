#include <algorithm>
#include <utility>
#include <vector>

class Solution {
 public:
  void nextPermutation(std::vector<int>& nums) {
    // std::next_permutation(nums.begin(), nums.end());
    // Notice that if the array is already sorted in descending order, no next
    // larger permutation is possible. Circle back.
    // Therefore, we need to find the first pair of numbers from the right,
    // nums[i] and nums[i-1] such that and nums[i] > nums[i-1].
    // 1 2 3
    // 1 3 2
    // 2 1 3
    // 2 3 1
    // 3 1 2
    // 3 2 1
    int i = nums.size() - 2;
    while (i >= 0 && nums[i] >= nums[i + 1]) {
      // Find the first non-decreasing (increasing) element
      --i;
    }

    // if i is less than 0, that means that the array is in descending order.
    // Reverse. Otherwise, find the first nums[j], i < j such that
    // nums[i] < nums[j] and nums[i] > nums[j+1]. I.e. the next element
    if (i >= 0) {
      int j = nums.size() - 1;

      while (nums[i] >= nums[j]) {
        --j;
      }

      std::swap(nums[i], nums[j]);
    }
    reverse(nums.begin() + i + 1, nums.end());
  }
};
