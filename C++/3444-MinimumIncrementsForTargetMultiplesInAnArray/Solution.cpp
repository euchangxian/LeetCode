#include <algorithm>
#include <climits>
#include <cstddef>
#include <cstdlib>
#include <numeric>
#include <vector>

using i64 = long long;
class Solution {
 public:
  int minimumIncrements(std::vector<int>& nums, std::vector<int>& target) {
    // In a single operation, increment any element of nums by 1.
    // Return the minimum number of operations required so that each element in
    // target has at least one multiple in nums.
    //
    // Note the constraints:
    // - target.length <= 4, which is suspiciously small.
    //
    // Naive! whats the naive solution!!
    // for each target[i], find the minimum number of operation for 1 multiple?
    // Nope. The choice for the subsequent targets may depend on the current,
    // lowest common multiple! The increment operation should be done on the
    // num closest to the LCM.
    //
    // Then why not just take the LCM of all numbers in the target?
    // Take the extremely trivial counter-example of:
    // nums = {4, 10}, target = {3, 5}
    // LCM(3, 5) = 15, would result in incrementing 10 to 15, instead of
    // the optimal 4 -> 6.
    //
    // Hm. So is there an overlapping substructure?
    // Take a less trivial example, nums = {7, 14}, target = {3, 5}
    // Naively, incrementing 7 to 9, then 14 to 15 would result in wasted ops.
    // Taking the LCM(3, 5), then incrementing 14 to 15 is optimal.
    //
    // But following up, suppose target = {3, 5, 6}.
    // Then, LCM(3, 5, 6) = 30, but LCM(3, 6) = 12, and incrementing 7->12 and
    // 14->15 is optimal now, instead of incrementing 14->30.
    //
    // Therefore, it seems that there is a choice between considering a single
    // element, and considering the LCM of > 1 elements.
    //
    // Therefore, we have:
    // f(nums, target) = min{
    //   f(nums, target\{target[i, .., j]}) + f(nums, target[i, .., j])
    // }
    // i.e., consider the min of subsets of targets.
    // Subsets => bitmasks! In this case, we need at most 4 bits, 1 << 4,
    // 2^4 = 16 possible subsets only.
    // Each subproblem (computing the min increments of the LCM of a subset)
    // takes O(n) time (find the closest number).
    // Thus, 16 distinct subproblems taking O(n) time each.
    //
    // With this, we can have dp[mask] representing the minimum number of ops.
    // for the subset represented by the mask.
    // dp[mask] = min{
    //   for all submasks s of mask:
    //     getMinOpsForLCM(submask) + dp[mask XOR submask]
    // }
    //
    // WARNING: 1 single target mask is not sufficient to ensure correctness.
    // There is a need to keep track of which number in nums was modified.
    // E.g., nums = [8, 10, 9], target = [10, 6, 6].
    // This above dp[111] would be equal to dp[011] + dp[100], as dp[011] would
    // modify 10 -> 12 for LCM(6, 6) = 6, while the same dp[100] would modify
    // 10 -> 10 for LCM(10) = 10.
    // Thus, there is a need to keep track of an additional state idx,
    // where idx represents the number in nums that was used/modified already.
    const int n = nums.size();
    const int k = target.size();

    // compute LCMs for all subsets.
    std::vector<i64> lcms(1 << k);
    for (int mask = 1; mask < (1 << k); ++mask) {
      i64 lcm = target[__builtin_ctz(mask)];  // first number in the subset.
      for (int bit = 0; bit < k; ++bit) {
        if (mask & (1 << bit)) {
          lcm = std::lcm(lcm, target[bit]);
        }
      }
      lcms[mask] = lcm;
    }

    // dp[i][mask] represents the min ops required when considering nums[i:]
    // and mask represents satisfied targets.
    std::vector<std::vector<i64>> memo(n + 1,
                                       std::vector<i64>(1 << k, LLONG_MAX));

    int fullMask = (1 << k) - 1;
    return dfs(nums, target, lcms, memo, fullMask, 0, 0);
  }

 private:
  i64 numOpsRequired(int num, i64 lcm) const {
    // determine LCM(mask_lcm, num)
    i64 nextMultiple = ((num + lcm - 1) / lcm) * lcm;
    return nextMultiple - num;
  }

  i64 dfs(const std::vector<int>& nums,
          const std::vector<int>& target,
          const std::vector<i64>& lcms,
          std::vector<std::vector<i64>>& memo,
          const int fullMask,
          int idx,
          int satisfied) const {
    if (satisfied == fullMask) {
      return 0;
    }

    if (idx >= nums.size()) {
      return LLONG_MAX;
    }

    if (memo[idx][satisfied] != LLONG_MAX) {
      return memo[idx][satisfied];
    }

    i64 minOps = dfs(nums, target, lcms, memo, fullMask, idx + 1, satisfied);

    // NOTE: see CP4 on generating proper subsets...
    // Remaining targets to make multiples of.
    int mask = fullMask & ~satisfied;
    for (int submask = mask; submask; submask = (submask - 1) & mask) {
      i64 take = numOpsRequired(nums[idx], lcms[submask]);
      i64 next =
          dfs(nums, target, lcms, memo, fullMask, idx + 1, satisfied | submask);

      if (next != LLONG_MAX) {
        minOps = std::min(minOps, take + next);
      }
    }
    return memo[idx][satisfied] = minOps;
  }
};
