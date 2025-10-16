#include <ranges>
#include <vector>

class Solution {
 public:
  int findSmallestInteger(std::vector<int>& nums, int value) {
    // In one operation, add or subtract value from any element in nums.
    // Return the maximum MEX (smallest missing non-negative integer) of nums
    // after any number of operations.
    //
    // The MEX is only as big as N.
    // Seems like a multiples/remainder-ish problem, where numbers that have
    // the same remainder mod value belong to the same group, and we can obtain
    // as many from that group.
    // Need to handle negatives.
    const auto n = static_cast<int>(nums.size());

    auto modulo = [value](int x) { return ((x % value) + value) % value; };

    std::vector<int> freq(value, 0);
    for (auto x : nums | std::views::transform(modulo)) {
      ++freq[x];
    }

    for (int mex : std::views::iota(0, n)) {
      if (freq[modulo(mex)]-- == 0) {
        return mex;
      }
    }
    return n;
  }
};
