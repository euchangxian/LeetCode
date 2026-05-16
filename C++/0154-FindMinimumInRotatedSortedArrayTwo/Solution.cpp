#include <vector>

class Solution {
 public:
  int findMin(std::vector<int>& nums) {
    // Sorted array rotated between [1..n] times.
    // Given that the sorted array nums may contain duplicates, return the
    // minimum element of this array.
    //
    // If it's all duplicates, then looking left/right will just degenerate into
    // a linear search.
    // Otherwise, we can try to minimise the search space by comparing
    // nums[pivot/mid] to nums[right].
    // - nums[mid] < nums[right]: mid is pivot, or on the left, right=mid
    // - nums[mid] > nums[right]: pivot is on the right, left=mid+1
    // - duplicate, linear search, shrink right.
    const auto n = static_cast<int>(nums.size());
    auto left = 0;
    auto right = n - 1;

    while (left < right) {
      auto pivot = left + (right - left) / 2;

      if (nums[pivot] < nums[right]) {
        right = pivot;
      } else if (nums[pivot] > nums[right]) {
        left = pivot + 1;
      } else {
        --right;
      }
    }
    return nums[left];
  }
};
