#include <bitset>
#include <queue>
#include <vector>

constexpr int MAX_N = 1000;
using NodeSet = std::bitset<MAX_N + 1>;

class Solution {
 public:
  std::vector<std::vector<int>> getAncestors(
      int n,
      std::vector<std::vector<int>>& edges) {
    // Given n representing the number of nodes in a DAG, numbered 0 to n-1.
    // edges[i] = [from, to] denoting a directed edge from node from to node to.
    // Return answer, where answer[i] is the list of ancestors of the ith node,
    // sorted in ascending order.
    //
    // Topological Sort.
    std::vector<std::vector<int>> adj(n);
    std::vector<int> indegree(n, 0);
    for (const auto& edge : edges) {
      auto from = edge[0];
      auto to = edge[1];

      adj[from].push_back(to);
      ++indegree[to];
    }

    std::queue<int> frontier;
    for (int i = 0; i < n; ++i) {
      if (indegree[i] == 0) {
        frontier.push(i);
      }
    }

    std::vector<NodeSet> ancestors(n);
    std::vector<int> nodes;
    nodes.reserve(n);
    while (!frontier.empty()) {
      auto curr = frontier.front();
      frontier.pop();

      nodes.push_back(curr);
      for (auto next : adj[curr]) {
        ancestors[next].set(curr);
        ancestors[next] |= ancestors[curr];

        if (--indegree[next] == 0) {
          frontier.push(next);
        }
      }
    }

    std::vector<std::vector<int>> result(n);
    for (int node = 0; node < n; ++node) {
      for (int ancestor = 0; ancestor < n; ++ancestor) {
        if (ancestors[node].test(ancestor)) {
          result[node].push_back(ancestor);
        }
      }
    }
    return result;
  }
};
