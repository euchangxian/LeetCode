#include <algorithm>
#include <climits>
#include <cstddef>
#include <cstdlib>
#include <queue>
#include <utility>
#include <vector>

class Solution {
 public:
  int mostProfitablePath(std::vector<std::vector<int>>& edges,
                         int bob,
                         std::vector<int>& amount) {
    // undirected tree with n nodes
    // edges[i] = [a, b] indicating an edge between (a, b).
    // amount[i] indicate the cash gained/lost at each node.
    // The cash is for the first visit only.
    // Alice starts at Node 0, moves towards some leaf node.
    // Bob starts at Node bob, moves towards Node 0.
    // If both Alice/Bob reaches the same node at the same time, then they
    // share the profit/cost.
    // Return maximum net income Alice can have.
    // First is, there is only one path from Node Bob to Node 0, while there
    // are multiple paths from root to leaf.
    // Depending on the depth, some nodes may be shared, others won't.
    // Feels like bi-directional BFS (but for Bob, its just a straight-line DFS)
    // where each iteration, advance both Alice and Bob, accounting for the max
    // profit at each node.
    // Observe that there is at most one node where both Alice and Bob will
    // meet simultaneously.
    const int n = edges.size() + 1;

    std::vector<std::vector<int>> adj(n);
    // assumes edges are provided in root-to-leaf manner, i.e., [parent, child]
    // NOTE: can't assume that.
    for (const auto& edge : edges) {
      int u = edge[0], v = edge[1];
      adj[u].push_back(v);
      adj[v].push_back(u);
    }

    std::vector<int> parent = [n, &adj]() -> std::vector<int> {
      std::vector<int> parent(n);
      parent[0] = -1;
      std::queue<int> frontier;
      frontier.push(0);
      while (!frontier.empty()) {
        int curr = frontier.front();
        frontier.pop();

        for (int next : adj[curr]) {
          if (next != parent[curr]) {
            parent[next] = curr;
            frontier.push(next);
          }
        }
      }
      return parent;
    }();

    std::vector<bool> seen(n, false);
    std::queue<std::pair<int, int>> frontier;  // {node, profit}
    frontier.emplace(0, 0);
    seen[0] = true;

    int best = INT_MIN;
    while (!frontier.empty()) {
      int sz = frontier.size();
      while (sz--) {
        auto [curr, profit] = frontier.front();
        frontier.pop();

        if (curr == bob) {
          profit += amount[curr] / 2;
        } else {
          profit += amount[curr];
        }

        bool leaf = true;
        for (int next : adj[curr]) {
          if (!seen[next]) {
            seen[next] = true;
            frontier.emplace(next, profit);
            leaf = false;
          }
        }

        if (leaf) {
          best = std::max(best, profit);
        }
      }

      amount[bob] = 0;  // clear the visited node.
      if (parent[bob] != -1) {
        bob = parent[bob];
      }
    }
    return best;
  }
};
