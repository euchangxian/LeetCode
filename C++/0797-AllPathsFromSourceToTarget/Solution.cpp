#include <vector>

class Solution {
 public:
  std::vector<std::vector<int>> allPathsSourceTarget(
      std::vector<std::vector<int>>& graph) {
    // Find all possible paths from source to target, return in any order.
    // DP on DAG.
    // DFS works. BFS works.
    // DFS should be simpler
    const int n = graph.size();

    std::vector<std::vector<int>> result;
    std::vector<int> curr;
    curr.reserve(n);

    dfs(graph, n - 1, 0, curr, result);
    return result;
  }

 private:
  void dfs(const std::vector<std::vector<int>>& adj,
           const int target,
           int u,
           std::vector<int>& path,
           std::vector<std::vector<int>>& result) {
    path.push_back(u);
    if (u == target) {
      result.push_back(path);
    } else {
      for (int v : adj[u]) {
        dfs(adj, target, v, path, result);
      }
    }
    path.pop_back();
  }
};
