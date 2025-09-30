#include <limits>
#include <vector>

class Solution {
 public:
  bool canDivideIntoSubsequences(std::vector<int>& nums, int k) {
    // Given nums sorted in non-decreasing order, and positive integer k.
    // Return true if this array can be divided into one or more DISJOINT
    // INCREASING subsequence of at least length k.
    //
    // This can be reduced to pigeonhole principle.
    // We can have at most x = nums.size()/k subsequences.
    // Since we want strictly increasing, we can have at most x copies of a
    // specific element.
    const auto n = static_cast<int>(nums.size());
    int prev = std::numeric_limits<int>::max();
    int count = 0;
    for (auto x : nums) {
      if (x != prev) {
        prev = x;
        count = 1;
      } else {
        if (++count * k > n) {
          return false;
        }
      }
    }
    return true;
  }
};
