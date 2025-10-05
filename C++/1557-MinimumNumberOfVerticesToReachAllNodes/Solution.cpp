#include <vector>

class Solution {
 public:
  std::vector<int> findSmallestSetOfVertices(
      int n,
      std::vector<std::vector<int>>& edges) {
    // Given a DAG with n vertices, edges[i] = [from, to], return the smallest
    // set of vertices from which all nodes in the graph are reachable, i.e.,
    // connected component.
    //
    // Hm. If indegree is 0, that node must be included in the final result.
    // If indegree is >0, then it will be reachable transitively after starting
    // at any node with indegree 0?
    // Can we prove this?
    std::vector<int> indegree(n, 0);
    for (const auto& edge : edges) {
      const auto to = edge[1];
      ++indegree[to];
    }

    std::vector<int> result;
    result.reserve(n);
    for (int i = 0; i < n; ++i) {
      if (indegree[i] == 0) {
        result.emplace_back(i);
      }
    }
    return result;
  }
};
