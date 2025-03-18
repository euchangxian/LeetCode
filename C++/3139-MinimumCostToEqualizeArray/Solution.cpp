#include <algorithm>
#include <climits>
#include <vector>

using i64 = long long;
constexpr int MOD = 1e9 + 7;
class Solution {
 public:
  int minCostToEqualizeArray(std::vector<int>& nums, int cost1, int cost2) {
    // any number of times:
    // - increment nums[i] by 1 for a cost of cost1, or
    // - increment nums[i] and nums[j] by 1 for a cost of cost2.
    // Minimum cost to make all elements in the array equal.
    //
    // We definitely want to avoid simulating.
    // If cost1*2 <= cost2, then the solution will be trivial: increment all
    // nums[i] such that nums[i] = max(nums)
    //
    // NOTE: not correct, see counter-example below.
    // Otherwise, we want to perform cost2-operations until there is 1 element
    // remaining that is not equal. Then do a final cost1-operation.
    // Can we prove that max(nums) never need to be incremented? i.e., in both
    // cases, we want to increment every other element to match max(nums).
    //
    // What if cost2 is extremely low, while cost1 is extremely high?
    // e.g., cost1=1e6, cost2=1.
    // nums = {1, 2, 3}
    // cost2(1, 2) => nums={2, 3, 3}
    // cost1(1)    => nums={3, 3, 3}
    // Total Cost = 1+1e6
    // Can we do better?
    //
    // cost2(1,2): {2, 3, 3}
    // cost2(1,2): {3, 4, 3}
    // cost2(1,3): {4, 4, 4}
    // Total Cost = 3
    // ....
    // Wew. This complicates things a little. Can we still identify a strategy?
    // Note that we only need to consider the case where cost1*2 > cost2,
    // which means that we want to do cost2-operations as many as we can.
    // What about BSTA on the max value? Nope. Cost function is not monotonic
    // based off max value. Though, the search space of the max(num) is
    // definitely finite, and doesnt deviate much.
    //
    // At this point, there are two problems to solve, lol:
    // 1. Determining the search space of max(nums), probably a function of
    //    cost1 and cost2, since we will only increment max(nums) when
    //    incurring cost2 multiple times is deemed more optimal than incurring
    //    cost1 a single time.
    // 2. Determining how many cost2 operations can be used, i.e., maximising
    //    cost2 operations.
    // 1:
    // A loose upperbound should be cost1 / (cost1-cost2)?
    //
    // 2:
    // Seems like a variant of 1953. Maximum Number of Weeks You can Work, where
    // cost2 is equivalent to interleaving the maxDiff with a non-max.
    // i.e., need to determine the number of pairings.
    const int n = nums.size();
    i64 sum = 0LL;
    int maxNum = INT_MIN;
    int minNum = INT_MAX;
    for (int num : nums) {
      maxNum = std::max(maxNum, num);
      minNum = std::min(minNum, num);
      sum += num;
    }

    i64 totalIncrements = (1LL * maxNum * n) - sum;

    // Case 1: Increment to maxNum, using only ops1.
    if (cost1 * 2 <= cost2 || n <= 2) {
      return (totalIncrements * cost1) % MOD;
    }

    // Case 2: Increment to maxNum, maximising ops2, remaining with ops1.
    // 1. maxNum-minNum gives the minimum number of increments necessary to
    //    increment the minimum number to the target.
    // 2. We greedily assign these to ops2, multiplying by 2.
    // 3. Minus totalIncrements to determine the remaining number of increments,
    //    which also represents the minimum number of ops1 necessary (to raise
    //    minNum to maxNum).
    // Note that this refers to increments on a SINGLE element only.
    i64 solo = std::max(0LL, (maxNum - minNum) * 2LL - totalIncrements);
    i64 pairs = totalIncrements - solo;
    i64 ops1 = solo + (pairs % 2);
    i64 ops2 = pairs / 2;
    i64 case2 = ops1 * cost1 + ops2 * cost2;

    // Case 3: Increment to maxNum + x, maximising ops2, remaining with ops1.
    // To do this, we try to MAXIMISE the number of replacements of the
    // solo-increments with pair-increments.
    //
    // The number to be replaced can be derived from +x, the maxNum:
    // - For each increment to maxNum, i.e., x+=1, N more increments are
    //   necessary.
    // - Out of the N increments added, only N-1 increments can be paired to
    //   the existing solo operations (since an element cannot
    //   be paired with itself)
    // - By replacing N-1 solo with paired operations, we effectively reduce
    //   the total number of solo operations by 1.
    // - i.e., we repeatedly do (solo - (n-2)); ++x;
    totalIncrements += solo / (n - 2) * n;
    solo %= n - 2;

    // same formulas as in Case 2
    pairs = totalIncrements - solo;
    ops1 = solo + pairs % 2;
    ops2 = pairs / 2;
    i64 case3 = ops1 * cost1 + ops2 * cost2;

    // Case 4: Increment to maxNum + x, using only ops2.
    // To use only ops2 operations, the total number of increments must be even.
    // Thus, we try to add n, or 2*n increments.
    // - If totalIncrements is already even, adding 2*n (always even) will
    //   result in an even number.
    // - If totalIncrements is odd, then adding n will result in an even number.
    i64 case4 = LLONG_MAX;
    for (int i = 0; i < 2; ++i) {
      totalIncrements += n;
      case4 = std::min(
          case4, (totalIncrements % 2) * cost1 + (totalIncrements / 2) * cost2);
    }
    return static_cast<int>(std::min({case2, case3, case4}) % MOD);
  }
};
