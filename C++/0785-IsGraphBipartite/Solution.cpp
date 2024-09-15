#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <cstdint>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class Solution {
private:
  bool dfs(vector<vector<int>> const &graph, vector<int8_t> &color, int idx,
           int8_t currColor) {
    color[idx] = currColor;

    for (int const &neighbour : graph[idx]) {
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

public:
  bool isBipartite(vector<vector<int>> const &graph) {
    // graph is an adjacency list where graph[u] represents the neighbours of u
    size_t n = graph.size();

    // Graph coloring.
    // Traverse the graph starting from an arbitrary node. Assign a color to
    // this node, say red. For each of its neighbours, assign the other colour.
    // If there is a node has been visited, and the opposite color can not be
    // assigned, then the graph is not bipartite.
    // 0 represents unassigned. -1 represents RED. 1 represents BLUE.
    // Since the graph may not be connected, DFS would be simpler to implement.
    vector<int8_t> color(n, 0);

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
};
