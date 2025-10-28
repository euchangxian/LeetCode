#include <numeric>
#include <vector>

class Solution {
 public:
  int countValidSelections(std::vector<int>& nums) {
    // Select starting position curr such that nums[curr] == 0, choose a
    // direction left or right.
    // Repeat:
    // - if curr is out of range [0..n-1], end.
    // - if nums[curr] == 0, move in current direction (incr/decr curr)
    // - if nums[curr] > 0, decrement nums[curr] by 1, reverse direction and
    //   take a step
    // An initial position and direction (curr, dir) is valid if every element
    // in nums become 0 by the end.
    //
    // Simulation? Unlikely. 2 choices for each starting position.
    // If the prefix/suffix sum are equal, then both directions are valid.
    // If they differ by exactly one, then only one direction is valid.
    // Else, not possible.
    const auto n = static_cast<int>(nums.size());
    int prefix = std::accumulate(nums.begin(), nums.end(), 0);

    int result = 0;
    int suffix = 0;
    for (int i = n - 1; i >= 0; --i) {
      prefix -= nums[i];

      if (nums[i] == 0) {
        if (prefix == suffix) {
          result += 2;
        }

        if (std::abs(prefix - suffix) == 1) {
          ++result;
        }
      }

      suffix += nums[i];
    }
    return result;
  }
};
