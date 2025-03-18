#include <algorithm>
#include <array>
#include <vector>

class Solution {
 public:
  int deleteAndEarn(std::vector<int>& nums) {
    // Naive solution:
    // 1. Pick idx, recurse on nums \ {(nums[idx] - 1) U (nums[idx] + 1)}
    // 2. Skip idx, recurse on nums
    // Pick the max
    //
    // What are the subproblems?
    // Seems similar to House Robber, when adjacent houses cannot be robbed;
    // adjacent buckets cannot be taken
    constexpr std::size_t n = 10e4 + 1;
    // Directly count the total number of points achievable by taking the
    // number
    // `{}` is an empty initializer which value-initializes elements in the
    // array.
    std::array<int, n> points{};
    for (int num : nums) {
      points[num] += num;
    }

    int skipPrev = 0;
    int takePrev = 0;
    for (int i = 0; i < n; ++i) {
      int currMax = std::max(takePrev, skipPrev + points[i]);

      skipPrev = takePrev;
      takePrev = currMax;
    }

    return std::max(skipPrev, takePrev);
  }
};
