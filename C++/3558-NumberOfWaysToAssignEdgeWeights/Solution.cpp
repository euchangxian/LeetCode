#include <algorithm>
#include <vector>

constexpr int MOD = 1E9 + 7;
class Solution {
 public:
  int assignEdgeWeights(std::vector<std::vector<int>>& edges) {
    // Tree with n nodes [1..n].
    // edges[i] = [u,v] indicate an undirected edge between u and v.
    // Initially, all weight 0. Assign each edge a weight of either 1 or 2.
    // The cost between any two nodes u,v is the total weight of all edges in
    // the path connecting them.
    // Select any node x at the maximum depth.
    // Return the number of ways to assign edge weights in the path from node 1
    // to x such that the total cost is odd, modulo 1E9+7.
    //
    // Tree => 1 path between any two nodes.
    // k number of nodes at max depth d.
    // Parity-based question.
    constexpr auto binaryExp = [](long long base, int exp) {
      long long result = 1;
      while (exp) {
        if (exp & 1) {
          result = (result * base) % MOD;
        }
        base = (base * base) % MOD;
        exp >>= 1;
      }
      return result;
    };
    const auto n = static_cast<int>(edges.size() + 1);  // tree
    std::vector<std::vector<int>> adj(n + 1);           // 1-indexed

    for (const auto& edge : edges) {
      auto u = edge[0];
      auto v = edge[1];
      adj[u].emplace_back(v);
      adj[v].emplace_back(u);
    }

    auto dfs = [&](this auto&& dfs, auto curr, auto prev) -> int {
      auto depth = 0;
      for (auto next : adj[curr]) {
        if (next != prev) {
          depth = std::max(depth, dfs(next, curr) + 1);
        }
      }
      return depth;
    };

    return binaryExp(2, dfs(1, -1) - 1);
  }
};
