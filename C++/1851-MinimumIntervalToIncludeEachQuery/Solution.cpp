#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <queue>
#include <utility>
#include <vector>

class Solution {
 public:
  std::vector<int> minInterval(std::vector<std::vector<int>>& intervals,
                               std::vector<int>& queries) {
    // Sort both and process offline.
    // For intervals, sort by ascending start, tie broken by size of the
    // interval, i.e., ascending end.
    // For queries, sort by ascending point.
    // Then, when iterating through queries, if the current interval does not
    // cover the queried point, it will never cover any subsequent queried
    // points.
    // i.e., two pointers.
    // No. Take the simple counterexample:
    // intervals = [[1, 10], [2, 3]]
    // queries = [2]
    // This algorithm wrongly returns 10, instead of 2.
    //
    // Sort by end, tie-break by interval size in DESCENDING order, so there
    // wont be false negatives?
    // intervals = [[1, 10], [2, 3]]
    // queries = [1, 2, 10]
    // Ah, still not viable. 10 will not be covered by [2, 3].
    //
    // Feels like Segment Tree with Range Minimum Queries can solve this,
    // similar to 2736. Maximum Sum Queries, where a binary search is done on
    // the [left, right] to determine the valid range, then a RMQ(left, right)
    // is done.
    // This requires discretization and removal of redundant ranges such that
    // the intervals are non-overlapping. Not trivial.
    //
    // Binary Search/Line Sweep?
    // Sort by start still. Tie-breaks are not-important.
    // given query x, determine the minimum possible index where x is still
    // valid, i.e.,
    // std::lower_bound(left.begin(), left.end(), x).
    // and the maximum possible index where x is still valid, x <= left[j].
    // std::prev(std::upper_bound(left.begin(), left.end(), x))
    // Then do a linear search. Worst case O(n^2) though.
    //
    // Nope.
    // When iterating through the points, use a minHeap ordered by {size, end}.
    // Then, to answer a query,
    // first add the intervals that end before and on this point,
    // while removing points from the heap points that already ended.
    // Then take the top.
    //
    const int n = intervals.size();
    std::sort(intervals.begin(), intervals.end());

    std::vector<std::pair<int, int>> offline;
    offline.reserve(queries.size());
    for (int i = 0; i < queries.size(); ++i) {
      offline.emplace_back(queries[i], i);
    }
    std::sort(offline.begin(), offline.end());

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        std::greater<>>
        active;
    int i = 0;
    std::vector<int> answer(queries.size());
    for (const auto [point, idx] : offline) {
      while (i < n && (point >= intervals[i][0])) {
        // {size, end}.
        active.emplace(intervals[i][1] - intervals[i][0] + 1, intervals[i][1]);
        ++i;
      }

      while (!active.empty() && active.top().second < point) {
        active.pop();
      }

      int size = active.empty() ? -1 : active.top().first;
      answer[idx] = size;
    }
    return answer;
  }
};
