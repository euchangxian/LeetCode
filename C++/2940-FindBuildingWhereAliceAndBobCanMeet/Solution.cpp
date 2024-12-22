#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  std::vector<int> leftmostBuildingQueries(
      std::vector<int>& heights,
      std::vector<std::vector<int>>& queries) {
    // First glance felt like something to do with Monotonicity/Suffix.
    // Note that Alice and/or Bob can only move rightwards to a taller building,
    // given that they can only move to a building j iff
    // - i < j, and
    // - heights[i] < heights[j]
    // Hm... Naively, for each query, start from max(a_i, b_i) and check
    // rightwards to see if max(heights[a_i], heights[b_i]) < heights[j].
    // Need to handle Alice moving to Bob's building without Bob moving, and
    // vice versa.
    // O(n * q) time. TLE-ed.
    // Can we do better?
    // Hm. We want to have the list of buildings of increasing heights to the
    // right of each index, such that we can pick the leftmost quickly.
    // What about maintaining a Monotonic Stack/Vector, along with a Map to
    // the respective index in the monotonic vector, then we can bind the
    // search space and do a binary search? Hm. Not really...
    //
    // NOTE: Tapped out with hints.
    // Since we want a taller building on the RIGHT, we can iterate in reverse
    // order from right-to-left.
    // Then, maintain a monotonically decreasing stack.
    // When we encounter a new building i, while the top of the stack is shorter
    // or equal to heights[i], we pop it off.
    // Then, the top-most would be the left-most building on the right of i,
    // such that its height is taller. Otherwise, store -1.
    // This allows us to build the lookup table for the leftmost building that
    // is taller than heights[i].
    // The taller property is trivially fulfilled by the stack property.
    // The leftmost property is fulfilled by the stack property.
    // O(n + q) time.
    //
    // WARNING:
    // Ah. Not exactly correct. The leftmost may not be the optimal one.
    // Consider
    // heights = {9, 10, 1, 2, 10}
    // suffix = {1, -1, 3, 4, -1}
    // query = {0, 2}
    // The algorithm/lookup would then return index 3 (or index 1 at most),
    // instead of index 4, the next taller one.
    // This would have worked if the queries only had a single index. For
    // multiple indices, we need to preprocess the queries array in a more
    // sophisticated manner.
    //
    // NOTE: Tapped out on answer.
    // The queries array need to be preprocessed such that the we take the
    // rightmost building of each query, and the maximum height of the query.
    // Then, iterate in reverse order, maintaining a monotonic decreasing stack,
    // At each query, the search space is simply the monotonic stack, and it
    // can be binary searched using the maximum height of the query as the
    // lowerbound.
    std::vector<int> ans(queries.size(), -1);

    // WLOG, let Alice be the shorter, Bob taller.
    // Then, we also want to store the original index of the query, since the
    // answer, ans[i] must be the result of the ith query.
    std::vector<std::vector<std::pair<int, int>>> newQueries(heights.size());
    for (int i = 0; i < queries.size(); ++i) {
      int a = std::min(queries[i][0], queries[i][1]);
      int b = std::max(queries[i][0], queries[i][1]);

      if (a == b || heights[a] < heights[b]) {
        ans[i] = b;
      } else {
        // heights[a] must be greater than heights[b], given the above
        // precondition. Thus, use it as the threshold for the search.
        newQueries[b].emplace_back(heights[a], i);
      }
    }

    // store indices, in monotonically decreasing order of heights.
    std::vector<int> monoDecr;
    for (int i = heights.size() - 1; i >= 0; --i) {
      // We book-keep first, to possible reduce the size of the search space.
      while (!monoDecr.empty() && heights[i] >= heights[monoDecr.back()]) {
        monoDecr.pop_back();
      }
      monoDecr.push_back(i);

      for (const auto [threshold, idx] : newQueries[i]) {
        // Key points:
        // 1. monoDecr stores indices in decreasing height order
        // 2. Using reverse iterators transforms heights to increasing order,
        //    which is what std::lower_bound/std::upper_bound expects
        // 3. Using upper_bound because we need strictly taller buildings
        //    (lower_bound would include equal heights)
        // 4. val < heights[elem] in upper_bound means that we find the
        //    first element in the range that is greater than the threshold.
        auto it =
            std::upper_bound(monoDecr.rbegin(), monoDecr.rend(), threshold,
                             [&heights](int val, int elem) -> bool {
                               return val < heights[elem];
                             });

        if (it != monoDecr.rend()) {
          ans[idx] = *it;
        }
      }
    }

    return ans;
  }
};
