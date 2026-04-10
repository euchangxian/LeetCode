#include <algorithm>
#include <array>
#include <deque>
#include <limits>
#include <vector>

class Solution {
 public:
  int minimumDistance(std::vector<int>& nums) {
    // (i, j, k) is good if nums[i] == nums[j] == nums[k]
    // Distance of a good tuple is:
    // - abs(i-j) + abs(j-k) + abs(k-i).
    // Return the minimum possible distance of a good tuple, or -1 if none
    // exists.
    //
    // n <= 100
    // nums[i] <= n
    //
    // The smallest distance is obtained by consecutives.
    constexpr auto MAX_N = 100;
    const auto n = static_cast<int>(nums.size());

    int result = std::numeric_limits<int>::max();
    std::array<std::deque<int>, MAX_N + 1> indices{};
    for (int i = 0; i < n; ++i) {
      auto& window = indices[nums[i]];
      window.push_back(i);

      if (window.size() > 3) {
        window.pop_front();
      }

      if (window.size() == 3) {
        // oh? 2*(window[2] - window[0])
        result = std::min(result, window[2] - window[1] + window[1] -
                                      window[0] + window[2] - window[0]);
      }
    }
    return result == std::numeric_limits<int>::max() ? -1 : result;
  }
};
