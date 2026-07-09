#include <vector>

class Solution {
 public:
  std::vector<bool> pathExistenceQueries(
      int n,
      std::vector<int>& nums,
      int maxDiff,
      std::vector<std::vector<int>>& queries) {
    // n nodes
    // nums sorted in non-decreasing order
    // An undirected edge between nodes i and j exists IF:
    // - |nums[i] - nums[j]| is at most maxDiff
    // queries[i] = [u, v], determine if there exists a PATH between u and v.
    //
    // Do not need Union Find, non-decreasing order. We can group nodes into
    // "components" just by doing a sliding window, then check comp[u]==comp[v].
    // No need sliding window. Just check adjacent.
    std::vector<int> component(n);
    auto comp = 0;
    component[0] = comp;

    for (auto i = 1; i < n; ++i) {
      if (nums[i] - nums[i - 1] > maxDiff) {
        ++comp;
      }
      component[i] = comp;
    }

    std::vector<bool> answer;
    answer.reserve(queries.size());
    for (const auto& query : queries) {
      auto u = query[0];
      auto v = query[1];

      answer.emplace_back(component[u] == component[v]);
    }
    return answer;
  }
};
