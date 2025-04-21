#include <algorithm>
#include <vector>

class Solution {
 public:
  int numberOfArrays(std::vector<int>& differences, int lower, int upper) {
    long long maxPositiveDelta = 0;
    long long minNegativeDelta = 0;

    long long prefixDiff = 0;
    for (int diff : differences) {
      prefixDiff += diff;
      maxPositiveDelta = std::max(maxPositiveDelta, prefixDiff);
      minNegativeDelta = std::min(minNegativeDelta, prefixDiff);
    }

    return std::max(
        0LL, (upper - maxPositiveDelta) - (lower - minNegativeDelta) + 1);
  }

  int numberOfArraysBranching(std::vector<int>& differences,
                              int lower,
                              int upper) {
    // n integers differences,
    // - differences[i] = nums[i+1] - nums[i]
    // - lower <= nums[i] <= upper
    // Return the number of possible sequences of nums.
    //
    // Hm. Considering differences[i], we can derive a tighter bound on
    // nums[i].
    // Considering differences[i] is a static value, we can reduce this problem
    // further into finding the number of possible values of nums[0].
    // Thus, can we iteratively tighten the bound?
    // Start with a range of possible starting values, and iteratively tighten
    // based off the PREFIX differences, since we only need to consider the
    // [start,end] of nums[0].
    // There wont be disjoint intervals.

    // maintain the lower/upper-bounds of nums[0]
    long long lb = lower;
    long long ub = upper;

    // can be positive/negative.
    // Must consider both lower <= lb/ub <= upper.
    // Can we do it more elegantly?
    // if we do not care about maintaining ub>=lb as a loop invariant?
    // - if prefixDiff < 0, then we update lb
    //   - lb = std::max(lb, lower - prefixDiff)
    // - if prefixDiff > 0, then we update ub
    //   - ub = std::min(ub, upper - prefixDiff)
    // In each step, the range of [lb..ub] is monotonically non-increasing.
    long long prefixDiff = 0;
    for (int diff : differences) {
      prefixDiff += diff;
      if (diff < 0) {
        lb = std::max(lb, lower - prefixDiff);
      } else {
        ub = std::min(ub, upper - prefixDiff);
      }
    }

    return std::max(0LL, ub - lb + 1);
  }
};
