#include <cstdint>
#include <vector>

class Solution {
 public:
  int numSubarrayProductLessThanK(std::vector<int>& nums, int k) {
    if (k <= 1) {
      return 0;
    }

    int32_t result{0};
    int32_t prod{1};
    std::size_t l{0};
    for (std::size_t r{0}; r < nums.size(); ++r) {
      prod *= nums[r];

      while (prod >= k) {
        prod /= nums[l++];
      }

      result += (r - l + 1);
    }
    return result;
  }
};
