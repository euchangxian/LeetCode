#include <bitset>
#include <vector>

class Solution {
 public:
  int missingInteger(std::vector<int>& nums) {
    // prefix(nums[0..1]) is sequential if:
    // - for all 1<=j<=i, nums[j] = nums[j-1]+1
    // Return the smallest integer x missing from nums such that x >= sum of
    // the longest sequential prefix.
    //
    // MUST START FROM index 0.
    constexpr auto MAX_VAL = 50;
    const auto n = static_cast<int>(nums.size());

    std::bitset<MAX_VAL + 1> seen{};
    seen.set(nums[0]);

    auto psum = nums[0];
    bool checkPsum = true;
    for (auto i = 1; i < n; ++i) {
      if (checkPsum) {
        if (nums[i] == nums[i - 1] + 1) {
          psum += nums[i];
        } else {
          checkPsum = false;
        }
      }
      seen.set(nums[i]);
    }

    while (psum <= MAX_VAL && seen.test(psum)) {
      ++psum;
    }
    return psum;
  }
};
