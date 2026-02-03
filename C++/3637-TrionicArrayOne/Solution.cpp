#include <vector>

class Solution {
 public:
  bool isTrionic(std::vector<int>& nums) {
    // an array is is trionic if there exists two indices p, q such that
    // 0 < p < q < n-1 (not first or last):
    // - nums[0..p] is strictly increasing
    // - nums[p..q] is strictly decreasing
    // - nums[q..n-1] is strictly increasing
    // return true if trionic, else false.
    //
    // Hm. zigzag array. Up, Down, Up.
    // Exactly two change in directions.
    // First direction must be up.
    const auto n = static_cast<int>(nums.size());
    if (nums[1] <= nums[0]) {
      return false;
    }

    int changes = 0;
    for (int i = 2; i < n; ++i) {
      if (nums[i] == nums[i - 1]) {
        return false;
      }
      if ((nums[i] - nums[i - 1]) * (nums[i - 1] - nums[i - 2]) < 0) {
        ++changes;
      }
    }
    return changes == 2;
  }
};
