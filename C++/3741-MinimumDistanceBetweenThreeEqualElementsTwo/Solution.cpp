#include <algorithm>
#include <array>
#include <limits>
#include <vector>

class Solution {
 public:
  int minimumDistance(std::vector<int>& nums) {
    constexpr std::size_t MAX_N = 1E5;
    const auto n = static_cast<int>(nums.size());

    int result = std::numeric_limits<int>::max();
    std::array<std::array<int, 2>, MAX_N + 1> indices;
    indices.fill({-1, -1});
    for (int k = 0; k < n; ++k) {
      auto& window = indices[nums[k]];
      auto& i = window[0];
      auto& j = window[1];
      if (i != -1 && j != -1) {
        result = std::min(result, j - i + k - j + k - i);
      }
      i = std::exchange(j, k);
    }
    return result == std::numeric_limits<int>::max() ? -1 : result;
  }
};
