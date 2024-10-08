#include <cstdint>
#include <vector>

using std::vector;
class Solution {
 public:
  int numSubarrayProductLessThanK(vector<int>& nums, int k) {
    if (k <= 1) {
      return 0;
    }

    int32_t result{0};
    int32_t prod{1};
    size_t l{0};
    for (size_t r{0}; r < nums.size(); ++r) {
      prod *= nums[r];

      while (prod >= k) {
        prod /= nums[l++];
      }

      result += (r - l + 1);
    }
    return result;
  }
};
