#include <algorithm>
#include <vector>

class Solution {
 public:
  long long maxTotalValue(std::vector<int>& nums, int k) {
    auto [min, max] = std::ranges::minmax(nums);
    return static_cast<long long>(max - min) * k;
  }
};
