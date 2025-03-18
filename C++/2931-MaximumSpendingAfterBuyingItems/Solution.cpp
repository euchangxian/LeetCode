#include <cstddef>
#include <functional>
#include <queue>
#include <utility>
#include <vector>

class Solution {
 public:
  long long maxSpending(std::vector<std::vector<int>>& values) {
    // m x n integer matrix values, each representing the value of an item.
    // m shops, n items each.
    // Items in the ith shop are sorted in non-increasing order of value, i.e.,
    // most expensive comes first.
    //
    // On each day, buy a single item from one of the shops.
    // - Pick any shop i
    // - Buy the rightmost available item j for the price of values[i][j] * d
    //
    // Hmm. Seems like DP? Considering for each day d, we have m choices, since
    // we can pick one of m shops.
    // Naively, that would result in an m^n runtime.
    // Memoizing it would require 3 states, m, n and d, where d = m * n
    // 1 <= m <= 10
    // 1 <= n <= 10^4
    // Seems like this would result in memory limit exceeded. 10^10
    // Are we able to exploit the sorted order?
    // Seems like we want to just push all rightmost item into a Heap, then
    // and repeatedly pop the lowest valued item first.
    // At any point in time, there would be m items in the heap, resulting in
    // logm pop/push per heap operation. There will be m * n items / heap ops,
    // resulting in a total TC of O(mnlogm)
    const std::size_t m = values.size();
    const std::size_t n = values[0].size();

    // stores {value, i = storeIndex}
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        std::greater<>>
        minHeap;

    // are we able to handle n = 1?
    for (int i = 0; i < m; ++i) {
      minHeap.emplace(values[i][n - 1], i);
    }

    // ptrs[i] indicate the index of the next item to be added into the heap.
    std::vector<int> ptrs(m, n - 2);

    long long result = 0LL;
    for (long long d = 1; d <= m * n; ++d) {
      auto [val, shop] = minHeap.top();
      minHeap.pop();

      result += (static_cast<long long>(val) * d);
      if (ptrs[shop] >= 0) {
        minHeap.emplace(values[shop][ptrs[shop]], shop);
        --ptrs[shop];
      }
    }

    return result;
  }
};
