#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <deque>
#include <functional>
#include <iostream>
#include <istream>
#include <iterator>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

constexpr auto valid = [](int n, int k) -> bool {
  while (n > 1) {
    n = n - k + 1;
  }
  return n == 1;
};

class Solution {
 public:
  int mergeStones(std::vector<int>& stones, int k) {
    // In one operation,
    // - pick k consecutive piles stones[i]..stones[j] and merge them.
    // - Add the sum of stones[i]..stones[j] to the cost.
    // There is an optimal strategy, since we need to return the minimum cost.
    // Notice that the earlier the stones are merged, the more they will be
    // used.
    // i.e., if 2 merges are required, then merging the larger stones first,
    // will involve merging the pile with the larger stone again.
    // e.g., [1, 1, 100]
    // first: merge(1, 100) => cost += 101
    // second: merge(1, 101) => cost += 102 = 203.
    // As oppposed to:
    // merge(1, 1) => cost += 2
    // merge(2, 100) => cost += 102 = 104.
    // Also, the position matters too, e.g., [1, 100, 1], where both merges
    // are forced to include the stone 100.
    //
    // Compute the prefix sum first. This allows us to retrieve the sum of the
    // subarray stones[l:l+k] efficiently. i.e., range sum queries.
    //
    // Are there subproblems? Feels like Burst Balloons, where doing it directly
    // requires continuously altering the state of the array. Not trivial.
    // Hm, but the "last" k piles will not work trivially too, given that the
    // state of 1 pile depends on "previous" merged piles/choices.
    // Choices involve last k-1 piles to be merged?
    // Then, the optimal "last" choice would be the piles with the greatest sum,
    // since we want to minimize the cost.
    // NOTE: certain "splits" must be pruned, since the resultant subarray may
    // not result in the valid amount of piles.
    //
    // Naively,
    // func dfs(stones, left, right):
    //   if (!valid(left, right)):
    //     return INF
    //   best := INF
    //   for i in [left..right-k]:
    //     cost := sum(stones[i:i+k-1]) + stones[right]
    //     subproblems := dfs(stones, left, i) +
    //                    dfs(stones, i+k, right)
    //     best = min(best, cost + subproblems)
    //   return best
    const int n = stones.size();
    if (!valid(n, k)) {
      return -1;  // simple, cheap check given n <= 30
    }
  }
};
