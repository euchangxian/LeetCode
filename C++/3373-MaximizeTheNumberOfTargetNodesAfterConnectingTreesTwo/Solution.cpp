#include <algorithm>
#include <array>
#include <vector>

enum Color {
  Red = 0,
  Blue = 1,
};

class Solution {
 public:
  std::vector<int> maxTargetNodes(std::vector<std::vector<int>>& edges1,
                                  std::vector<std::vector<int>>& edges2) {
    // Node u is target to node v if the number of edges on the path from u
    // to v is even.
    // Return answer, where answer[i] is the maximum target nodes if a node
    // from the first tree is connected to another node in the second tree.
    //
    // Given n, m <= 1e5, not feasible to brute force.
    // Instead, notice that unlike the first variant, there is no concept of
    // distance from root.
    // Instead, there are nodes that are optimal, i.e., the number of nodes at
    // even/odd distance away is maximum.
    //
    // Hm. Rooting at arbitrary node, say node 0.
    // If we do a level order traversal, parent nodes, and nodes on the same
    // level are odd distance away.
    // Also, nodes that are odd-distance from parents are even-distance to
    // the current node. DP-like.
    const int n = edges1.size() + 1;
    const int m = edges2.size() + 1;

    auto buildAdj = [](const auto& edges) {
      std::vector<std::vector<int>> adj(edges.size() + 1);
      for (const auto& edge : edges) {
        adj[edge[0]].push_back(edge[1]);
        adj[edge[1]].push_back(edge[0]);
      }
      return adj;
    };

    auto adj1 = buildAdj(edges1);
    auto adj2 = buildAdj(edges2);

    // bipartite coloring
    std::vector<Color> color1(n);
    std::vector<Color> color2(m);
    auto dfs = [&](this auto&& dfs, const auto& adj, auto& coloring, int curr,
                   Color color, int parent = -1) -> int {
      int countRed = color == Color::Red;
      coloring[curr] = color;
      for (int next : adj[curr]) {
        if (next == parent) {
          continue;
        }
        countRed += dfs(adj, coloring, next,
                        static_cast<Color>(1 - static_cast<int>(color)), curr);
      }
      return countRed;
    };

    int red1 = dfs(adj1, color1, 0, Color::Red);
    int blue1 = n - red1;

    int red2 = dfs(adj2, color2, 0, Color::Red);
    int blue2 = m - red2;

    std::array<int, 2> count1{{red1, blue1}};
    int count2 = std::max(red2, blue2);
    std::vector<int> answer(n);
    for (int i = 0; i < n; ++i) {
      answer[i] = count1[color1[i]] + count2;
    }
    return answer;
  }
};
