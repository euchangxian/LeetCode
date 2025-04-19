#include <algorithm>
#include <vector>

class Solution {
 public:
  int maximumRequests(int n, std::vector<std::vector<int>>& requests) {
    // N buildings,
    // requests[i]=[a, b] indicate an employee moving from building a to b.
    // Since each building is at capacity, the net change in employees must
    // remain 0.
    //
    // Count indegree, outdegree of each building, take min of each?
    // Seems too naive. This assumes all buildings in the chain can fulfil their
    // transfer requests. Is there a counter example?
    // requests  = [[0,0],[1,1],[0,0],[2,0],[2,2],[1,1],[2,1],[0,1],[0,1]]
    // indegree  = [3, 5, 1]
    // outdegree = [5, 2, 3]
    // Expected: 5, Actual: 6
    //
    // Given the small constraints n <= 20, requests.length <= 16, we can
    // brute force.
    // We can consider subset of requests.
    const int k = requests.size();
    const int fullMask = (1 << k) - 1;

    int result = 0;
    for (int i = 1; i < (1 << k); ++i) {
      int fulfilled = __builtin_popcount(i);
      if (fulfilled <= result) {
        // prune
        continue;
      }
      std::vector<int> netchange(n, 0);

      for (int mask = i; mask; mask &= (mask - 1)) {
        int idx = __builtin_ctz(mask);  // index of last set bit.
        const auto& edge = requests[idx];

        --netchange[edge[0]];
        ++netchange[edge[1]];
      }

      if (std::count(netchange.begin(), netchange.end(), 0) != n) {
        continue;
      }

      result = fulfilled;
    }
    return result;
  }
};
