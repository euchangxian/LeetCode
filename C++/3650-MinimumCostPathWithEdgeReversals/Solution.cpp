#include <functional>
#include <queue>
#include <utility>
#include <vector>

class Solution {
 public:
  int minCost(int n, std::vector<std::vector<int>>& edges) {
    // edges[i] = [u, v, w], representing a directed edge from u to v with
    // weight w.
    // Each node has a switch that can be used at most once, and when activated
    // on one of it's INCOMING edges, reverse that edge from v->u to u->v and
    // traverse it immediately.
    // Using a reversed edge is only valid for that single move, and costs 2*w.
    // Return the minimum cost from Node 0 to Node N-1.
    //
    // Seems like Dijkstra's.
    // Need to track the reversability. Or just add the edges in.
    constexpr int INF = 1E9;

    // u : {v, w}
    std::vector<std::vector<std::pair<int, int>>> adj(n);
    for (const auto& edge : edges) {
      auto u = edge[0];
      auto v = edge[1];
      auto w = edge[2];

      adj[u].emplace_back(v, w);
      adj[v].emplace_back(u, 2 * w);
    }

    // {totalCost, node}
    using QNode = std::pair<int, int>;
    std::priority_queue<QNode, std::vector<QNode>, std::greater<>> frontier;
    std::vector<int> distance(n, INF);
    frontier.emplace(0, 0);
    while (!frontier.empty()) {
      auto [total, curr] = frontier.top();
      frontier.pop();
      if (total > distance[curr]) {
        continue;
      }

      if (curr == n - 1) {
        return total;
      }

      for (auto [next, weight] : adj[curr]) {
        if (auto dist = total + weight; dist < distance[next]) {
          distance[next] = dist;
          frontier.emplace(dist, next);
        }
      }
    }
    return -1;
  }
};
