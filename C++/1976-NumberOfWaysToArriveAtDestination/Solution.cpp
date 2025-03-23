#include <functional>
#include <queue>
#include <utility>
#include <vector>

using i64 = long long;
constexpr i64 INF = 1e12;
constexpr int MOD = 1e9 + 7;

class Solution {
 public:
  int countPaths(int n, std::vector<std::vector<int>>& roads) {
    // n nodes [0..n-1].
    // roads[i] = [u, v, w], bidirectional with weight w.
    // Count number of ways to reach destination in shortest amount of time.
    //
    // Run Dijkstra's once. Then create a directed graph G' such that:
    // - The edge (u, v) is in G
    // - dist[u] + weight(u, v) = dist[v]
    // - dist[u] < dist[v]
    //
    // Then, we essentially get a directed acyclic graph, where we can then
    // count using DP.
    std::vector<std::vector<std::pair<int, int>>> adj(n);
    for (const auto& edge : roads) {
      int u = edge[0], v = edge[1], w = edge[2];
      adj[u].emplace_back(v, w);
      adj[v].emplace_back(u, w);
    }

    std::vector<i64> dist(n, INF);
    std::vector<int> paths(n, 0);
    std::priority_queue<std::pair<i64, int>, std::vector<std::pair<i64, int>>,
                        std::greater<>>
        pq;
    dist[0] = 0;
    paths[0] = 1;
    pq.emplace(0LL, 0);

    while (!pq.empty()) {
      auto [cost, curr] = pq.top();
      pq.pop();

      if (cost > dist[curr]) {
        continue;
      }

      for (const auto [next, w] : adj[curr]) {
        if (dist[curr] + w == dist[next]) {
          paths[next] = (1LL * paths[next] + paths[curr]) % MOD;
        } else if (dist[curr] + w < dist[next]) {
          paths[next] = paths[curr];
          dist[next] = dist[curr] + w;
          pq.emplace(dist[next], next);
        }
      }
    }

    return paths[n - 1];
  }
};
