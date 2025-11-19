#include <bitset>
#include <vector>

constexpr auto MAX_N = 1000;
class Solution {
 public:
  int findFinalValue(std::vector<int>& nums, int original) {
    // given integer original to be searched for in nums:
    // 1. if original is found in nums, multiply it by 2.
    // 2. otherwise, stop.
    // Return the final value of original.
    std::bitset<MAX_N + 1> seen{};
    for (auto x : nums) {
      seen.set(x);
    }

    while (original <= MAX_N && seen[original]) {
      original *= 2;
    }
    return original;
  }
};
