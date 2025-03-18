#include <utility>
#include <vector>

class Solution {
 public:
  // Essentially Three-way QuickSort. Pick '1' as pivot.
  void sortColors(std::vector<int>& nums) {
    int left = 0;  // the next index to place a '0' at.
    int right = nums.size() - 1;

    int mid = 0;
    while (mid <= right) {
      if (nums[mid] == 0) {
        std::swap(nums[left++], nums[mid++]);
      } else if (nums[mid] == 1) {
        mid++;
      } else {
        std::swap(nums[mid], nums[right--]);
      }
    }
  }
};
