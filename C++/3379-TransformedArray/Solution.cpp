#include <vector>

class Solution {
 public:
  std::vector<int> constructTransformedArray(std::vector<int>& nums) {
    // Given nums that represent a circular array.
    // Create a new array result.
    // For each index i (independently):
    // - if nums[i] > 0 => start at index i, move nums[i] steps to the right,
    //   set result[i] to nums[i+nums[i]].
    // - if nums[i] < 0 => start at index i, move nums[i] steps to the left,
    //   set result[i] to nums[i-nums[i]].
    // - if nums[i] == 0 => result[i] = nums[i].
    const auto n = static_cast<int>(nums.size());
    std::vector<int> result(n);
    for (int i = 0; i < n; ++i) {
      result[i] = nums[(((i + nums[i]) % n) + n) % n];
    }
    return result;
  }
};
