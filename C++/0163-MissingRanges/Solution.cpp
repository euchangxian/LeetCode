#include <utility>
#include <vector>

class Solution {
 public:
  std::vector<std::vector<int>> findMissingRanges(std::vector<int>& nums,
                                                  int lower,
                                                  int upper) {
    // Sorted array nums.
    // x is missing if x is in the range [lower..upper] and not in nums.
    // Return the shortest, sorted list of ranges that exactly covers all
    // the missing numbers.
    //
    // Iterate over nums, insert [lower, nums[i]-1] if nums[i] - 1 is not
    // covered.
    // update lower.
    const auto n = static_cast<int>(nums.size());
    if (nums.empty()) {
      return {{lower, upper}};
    }

    std::vector<std::vector<int>> result;
    for (auto x : nums) {
      if (lower == x) {
        ++lower;
      }

      if (x > lower) {
        result.push_back({std::exchange(lower, x + 1), x - 1});
      }
    }

    if (nums.back() != upper) {
      result.push_back({nums.back() + 1, upper});
    }

    return result;
  }
};
