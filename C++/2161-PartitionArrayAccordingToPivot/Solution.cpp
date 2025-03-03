#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <string_view>
#include <utility>
#include <vector>

class Solution {
 public:
  std::vector<int> pivotArray(std::vector<int>& nums, int pivot) {
    // 3-way Partition.
    // We want this parition step to be stable. Thus O(N) space is necessary.
    const int n = nums.size();

    // Count Less-Than and Equal-To
    int lt = 0;
    int eq = lt;
    for (int i = 0; i < n; ++i) {
      if (nums[i] < pivot) {
        ++lt;
      } else if (nums[i] == pivot) {
        ++eq;
      }
    }

    // determine the starting positions of each partition.
    int gt = lt + eq;
    eq = lt;
    lt = 0;
    std::vector<int> result(n);
    for (int i = 0; i < n; ++i) {
      if (nums[i] < pivot) {
        result[lt++] = nums[i];
      } else if (nums[i] == pivot) {
        result[eq++] = nums[i];
      } else {
        result[gt++] = nums[i];
      }
    }
    return result;
  }

  std::vector<int> pivotArrayNotStable(std::vector<int>& nums, int pivot) {
    const int n = nums.size();
    int lt = 0;
    int gt = n - 1;
    int eq = 0;  // also the scanning ptr.

    // NOTE: Not stable.
    while (eq <= gt) {
      if (nums[eq] < pivot) {
        std::swap(nums[lt], nums[eq]);
        ++lt;
        ++eq;
      } else if (nums[eq] == pivot) {
        ++eq;
      } else {
        std::swap(nums[gt--], nums[eq]);
      }
    }

    return nums;
  }
};
