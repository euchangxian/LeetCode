#include <algorithm>
#include <bitset>
#include <vector>

class Solution {
 public:
  std::vector<int> findMissingElements(std::vector<int>& nums) {
    // nums contain [smallest, largest], unique integers.
    // Find all missing integers in sorted order.
    //
    // Can we do 1-pass? Not really.
    constexpr auto MAX_VAL = 100;

    auto min = MAX_VAL + 1;
    auto max = 0;
    std::bitset<MAX_VAL + 1> seen{};
    for (auto x : nums) {
      seen.set(x);
      min = std::min(min, x);
      max = std::max(max, x);
    }

    std::vector<int> missing;
    missing.reserve(nums.size());
    for (auto x = min + 1; x < max; ++x) {
      if (!seen.test(x)) {
        missing.emplace_back(x);
      }
    }
    return missing;
  }
};
