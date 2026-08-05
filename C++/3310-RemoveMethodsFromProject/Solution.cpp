#include <bitset>
#include <ranges>
#include <vector>

class Solution {
 public:
  std::vector<int>
  remainingMethods(int n, int k, std::vector<std::vector<int>>& invocations) {
    // n nodes 0 to n-1.
    // invocations[i] = [a, b] indicate a directed edge from a to b.
    // Node k is buggy, any node that can be reached from node k are suspicious
    // and should be removed.
    // A component can only be removed if no nodes outside the component is
    // connected to a node within.
    // Return all the remaining nodes. If not possible to remove all suspicious
    // nodes, none should be removed.
    //
    // Sounded like SCC but not really - SCC requires every pair of nodes to
    // be reachable from each other.
    // This is simpler?
    // DFS and mark every node from node k, collecting all inbound nodes on
    // marked nodes.
    // Check that every inbound node is also reachable from k.
    constexpr int MAX_N = 1E5;

    std::vector<std::vector<int>> adj(n);
    for (const auto& edge : invocations) {
      auto from = edge[0];
      auto to = edge[1];
      adj[from].emplace_back(to);
    }

    std::bitset<MAX_N> suspicious{};
    suspicious.set(k);
    auto dfs = [&](this auto&& dfs, auto curr) -> void {
      for (auto next : adj[curr]) {
        if (!suspicious.test(next)) {
          suspicious.set(next);
          dfs(next);
        }
      }
    };
    dfs(k);

    for (const auto& edge : invocations) {
      auto from = edge[0];
      auto to = edge[1];
      if (!suspicious.test(from) && suspicious.test(to)) {
        // return all
        return std::views::iota(0, n) | std::ranges::to<std::vector>();
      }
    }

    std::vector<int> result;
    result.reserve(n);
    for (int i = 0; i < n; ++i) {
      if (!suspicious.test(i)) {
        result.emplace_back(i);
      }
    }
    return result;
  }
};
