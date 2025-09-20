#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstdint>
#include <deque>
#include <functional>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using i64 = long long;
class Solution {
 public:
  int minimumPairRemoval(std::vector<int>& nums) {
    // Given nums, perform the following operation:
    // - Select the adjacent pair with the minimum sum, tie-broken by leftmost,
    //   replace the pair with their sum.
    // until the array is non-decreasing, i.e., sorted order.
    //
    // There is no element of choice.
    // The selection of pairs can be done using a priority_queue, storing the
    // indices of the pair (i, j).
    // The indices remaining should be maintained with a Set, so that the
    // predecessor and succesor indices can be obtained to create the next sum.
    // Hm. More precisely, a std::map, since the values will be replaced with
    // their pair sum.
    // But how to efficiently determine that the array is sorted?
    // Maintain the count of inversions. When making the pair sum, if
    // nums[i+1] < nums[i], then increment the inversion.
    // Else, decrement.
    // Until 0.

    // {sum, index}
    // Note we do not need to keep both index, even though it is not guaranteed
    // that they are adjacent.
    // This is because we just need the predecessor/successor.
    const int n = nums.size();
    std::priority_queue<std::tuple<i64, int, int>,
                        std::vector<std::tuple<i64, int, int>>, std::greater<>>
        pq;

    // {index, sum}
    std::map<int, i64> active;
    int inversions = 0;
    for (int i = 0; i < n - 1; ++i) {
      if (nums[i] > nums[i + 1]) {
        ++inversions;
      }

      pq.emplace(nums[i] + nums[i + 1], i, i + 1);
      active.emplace(i, nums[i]);
    }
    active.emplace(n - 1, nums[n - 1]);

    while (inversions > 0) {
      // note that by taking this pair, we need to check if it has already been
      // invalidated.
      auto [sum, i, j] = pq.top();
      pq.pop();

      auto it = active.find(i);
      auto succ = active.find(j);
      if (it == active.end() || succ == active.end()) {
        // no longer valid.
        continue;
      }

      if (it != active.begin()) {
        auto pred = std::prev(it);
        int next = sum + pred->second;

        pq.emplace(next, pred->first, i);
        it->second = next;
      }

      succ = std::next(succ);
      int next = sum + succ->second;
      pq.emplace(next, i, succ->first);
    }
  }
};
