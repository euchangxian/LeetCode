#include <algorithm>
#include <cstddef>
#include <utility>
#include <vector>

class Solution {
 public:
  int removeElement(std::vector<int>& nums, int val) {
    // order of elements may be changed. Remove occurences of val.
    // simply swap
    int i = 0;
    int n = nums.size();

    while (i < n) {
      while (i < n && nums[i] == val) {
        std::swap(nums[i], nums[n - 1]);
        --n;
      }
      ++i;
    }

    return n;
  }
};
