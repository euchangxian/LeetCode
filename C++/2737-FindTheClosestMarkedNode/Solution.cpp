#include <functional>
#include <queue>
#include <utility>
#include <vector>

constexpr int INF = 1e9;
class Solution {
 public:
  int minimumDistance(int n,
                      std::vector<std::vector<int>>& edges,
                      int s,
                      std::vector<int>& marked) {
    // n: number of nodes labelled [0..n-1]
    // edges[i] = [u, v, w] indicating a directed, weighted edge from u to v.
    //
    // find the minimum distance from node s to any of the marked nodes.
    // Reverse edges, Dijkstra from marked nodes to s?
    std::vector<std::vector<std::pair<int, int>>> adj(n);
    for (const auto& edge : edges) {
      int u = edge[0], v = edge[1], w = edge[2];
      adj[v].emplace_back(u, w);
    }

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        std::greater<>>
        minHeap;
    std::vector<int> dist(n, INF);
    for (int u : marked) {
      dist[u] = 0;
      minHeap.emplace(0, u);
    }

    while (!minHeap.empty()) {
      const auto [_, curr] = minHeap.top();
      minHeap.pop();

      if (curr == s) {
        return dist[curr];
      }

      for (const auto [next, weight] : adj[curr]) {
        if (dist[curr] + weight < dist[next]) {
          dist[next] = dist[curr] + weight;
          minHeap.emplace(dist[next], next);
        }
      }
    }

    return -1;
  }
};
