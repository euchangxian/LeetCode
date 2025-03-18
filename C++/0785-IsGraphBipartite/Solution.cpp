#include <cstdint>
#include <vector>

class Solution {
 public:
  bool isBipartite(const std::vector<std::vector<int>>& graph) {
    // graph is an adjacency list where graph[u] represents the neighbours of u
    size_t n = graph.size();

    // Graph coloring.
    // Traverse the graph starting from an arbitrary node. Assign a color to
    // this node, say red. For each of its neighbours, assign the other colour.
    // If there is a node has been visited, and the opposite color can not be
    // assigned, then the graph is not bipartite.
    // 0 represents unassigned. -1 represents RED. 1 represents BLUE.
    // Since the graph may not be connected, DFS would be simpler to implement.
    std::vector<int8_t> color(n, 0);

    for (int i = 0; i < n; ++i) {
      if (!color[i]) {
        bool isValid = dfs(graph, color, i, 1);
        if (!isValid) {
          return false;
        }
      }
    }
    return true;
  }

 private:
  bool dfs(const std::vector<std::vector<int>>& graph,
           std::vector<int8_t>& color,
           int idx,
           int8_t currColor) {
    color[idx] = currColor;

    for (int neighbour : graph[idx]) {
      if (color[neighbour] == currColor) {
        return false;
      }

      if (!color[neighbour]) {
        if (!dfs(graph, color, neighbour, -currColor)) {
          return false;
        }
      }
    }
    return true;
  }
};
