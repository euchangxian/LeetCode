#include <algorithm>
#include <vector>

class Solution {
 public:
  int maximumProduct(std::vector<int>& nums) {
    // Find three numbers whose product is maximum. Return Product.
    // -1000 <= nums[i] <= 1000
    //
    // Two Negative, 1 Positive or Three Positive.
    const auto n = static_cast<int>(nums.size());
    std::ranges::sort(nums);

    return std::max(nums[0] * nums[1] * nums[n - 1],
                    nums[n - 1] * nums[n - 2] * nums[n - 3]);
  }
};
