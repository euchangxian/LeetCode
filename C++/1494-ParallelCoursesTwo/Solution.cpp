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

class Solution {
 public:
  int minNumberOfSemesters(int n,
                           std::vector<std::vector<int>>& relations,
                           int k) {
    // similar to Parallel Course Three.
    // Except we can only take at most k courses at once.
    // Still seems like a topological sort. But with some sort of scheduling?
    // Seems more difficult implementation-wise.
    // Constraints seem weirdly small though, n<=15.
    // Seems like we want to perform the courses in a way that maximises
    // concurrency.
    // Probably a brute-force/backtrack approach, since scheduling is NP-Hard.
    // At each step, pick K courses, decrement the respective indegrees of
    // the neighbouring courses. Recurse.
    // How to pick K courses though. Bitmasking.
    // dfs(...) = min(ans, 1 + dfs(...))
    std::vector<std::vector<int>> adj(n);
    std::vector<int> indegree(n, 0);
    for (const auto& edge : relations) {
      int u = edge[0] - 1, v = edge[1] - 1;
      adj[u].push_back(v);
      ++indegree[v];
    }

    std::vector<int> memo(1 << n, -1);
    return dfs(n, k, adj, indegree, memo, (1 << n) - 1);
  }

 private:
  int dfs(int n,
          int k,
          std::vector<std::vector<int>>& adj,
          std::vector<int>& indegree,
          std::vector<int>& memo,
          int mask) {
    int count = __builtin_popcount(mask);
    if (count == n) {
      return 0;
    }
  }
};
