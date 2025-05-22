#include <algorithm>
#include <queue>
#include <vector>

constexpr int MAX_N = 1E5;
class Solution {
 public:
  int maxRemoval(std::vector<int>& nums,
                 std::vector<std::vector<int>>& queries) {
    // queries[i] = [l, r]
    // For each query:
    // - Decrement the value at each index in the range [l, r] by at most 1
    // - Amount can be chosen independently.
    // Return the maximum number of queries that can be removed such that nums
    // can still be converted to a zero array.
    //
    // At first glance, a difference array, then the maximum overshoot is the
    // minimum number of removals we can make.
    // But we need the maximum.
    //
    // Feels like sorting is needed somehow + Greedy/DP, i.e., an interval
    // question.
    // We kinda want to remove the smallest intervals first, i.e., greedily.
    // So, sort by start ascending, then end descending.
    // For each nums[i] considered, pick the intervals greedily to reduce it
    // to 0.
    const int n = nums.size();
    const int q = queries.size();
    std::ranges::sort(queries, {}, [](const auto& q) { return q[0]; });

    int ops = 0;
    std::priority_queue<int> pq;  // Keep the latest ending intervals
    std::array<int, MAX_N + 1> diff{};
    for (int i = 0, qIdx = 0; i < n; ++i) {
      ops += diff[i];

      while (qIdx < q && queries[qIdx][0] <= i) {
        pq.push(queries[qIdx++][1]);
      }
      while (ops < nums[i] && !pq.empty() && pq.top() >= i) {
        // pick the latest ending.
        ++ops;
        --diff[pq.top() + 1];
        pq.pop();
      }

      if (ops < nums[i]) {
        return -1;
      }
    }

    // shortest intervals that can be removed.
    return pq.size();
  }
};
