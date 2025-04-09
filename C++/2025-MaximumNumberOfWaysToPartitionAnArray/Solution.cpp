#include <algorithm>
#include <functional>
#include <numeric>
#include <unordered_map>
#include <vector>

using i64 = long long;

class Solution {
 public:
  int waysToPartition(std::vector<int>& nums, int k) {
    // Given nums, find the maximum number of ways to partition nums, such that
    // - 1 <= pivot < n (pivot index)
    // - nums[0] +... + nums[pivot-1] == nums[pivot] + ... +nums[n-1],
    //   i.e., sum(nums[:pivot-1]) == sum(nums[pivot:])
    // with at most one operation to change an element to k.
    //
    // WARNING: DP is completely wrong approach.
    // Naively, i = pivot-1, sum = target sum == total/2:
    // dfs(i, sum, ops) = max{
    //   dfs(i+1, sum + nums[i], ops),
    //   dfs(i+1, sum+k, ops-1) if ops > 0
    // }
    //
    // Consider the reduced version first - No operations applied:
    // Then, we can precompute the prefix and suffix sums at index i,
    // such that prefix[i] = nums[0] + ... + nums[i-1] (exclude i)
    //           suffix[i] = nums[i] + ... + nums[n-1] (include i)
    // Then, we can determine the number of pivots by iterating over
    // p in [0..n-2], where prefix[i] == suffix[i]
    // In other words, suppose we have diff[i] = perfix[i] - suffix[i].
    // Then, we can count diff[i] == 0. (this formulation helps us later).
    //
    // Suppose we now allow an operation. Consider the effects on diff[i].
    // Given that diff[i] = prefix[i] - suffix[i]
    //                    = (nums[0]+...+nums[i-1]) - (nums[i]+...+nums[n-1])
    // Upon changing nums[i] = K, we get:
    // diffOp[i] = prefix[i] - (K+...+nums[n-1]) such that
    // - diff[j]-diffOp[j] = K-nums[j] for j in [0..i]
    // - diff[j]-diffOp[j] = nums[j]-K for j in [i+1..n-1]
    const int n = nums.size();
    const i64 sum = std::reduce(nums.begin(), nums.end(), 0LL, std::plus<>{});

    std::unordered_map<i64, int> prefixDiff, suffixDiff;
    prefixDiff.reserve(n), suffixDiff.reserve(n);

    i64 prefix = 0LL;
    for (int i = 0; i < n - 1; ++i) {  // for each pivot in [0..n-2]
      prefix += nums[i];
      i64 suffix = sum - prefix;
      ++suffixDiff[prefix - suffix];  // No operation applied yet.
    }

    int pivots = suffixDiff[0LL];  // diff 0, no operation applied.
    prefix = 0LL;
    for (int i = 0; i < n; ++i) {
      prefix += nums[i];
      i64 suffix = sum - prefix;
      i64 d = k - nums[i];

      // If we apply the operation on nums[i], i.e., replace nums[i] with k:
      // - For partitions before i: difference changes by +d
      // - For partitions after i: difference changes by -d
      // Thus, giving us the number of such pivot points.
      pivots = std::max(pivots, prefixDiff[d] + suffixDiff[-d]);

      // Transfer count from suffix to prefix.
      --suffixDiff[prefix - suffix];
      ++prefixDiff[prefix - suffix];
    }
    return pivots;
  }
};
