#include <algorithm>
#include <vector>

class Solution {
 public:
  std::vector<std::vector<int>> divideArray(std::vector<int>& nums, int k) {
    // Divide nums into n/3 arrays of size 3, where
    // - the difference between any two elements in each array is less than
    //   or equal to k.
    // Return any.
    // Sort? fixed size window of 3.
    const int n = nums.size();
    std::ranges::sort(nums);

    std::vector<std::vector<int>> result;
    result.reserve(n / 3);
    for (int i = 0; i < n; i += 3) {
      if (nums[i + 2] - nums[i] > k) {
        return {};
      }
      result.emplace_back(
          std::initializer_list<int>{nums[i], nums[i + 1], nums[i + 2]});
    }
    return result;
  }
};
