#include <algorithm>
#include <functional>
#include <queue>
#include <ranges>
#include <utility>
#include <vector>

using i64 = long long;
constexpr i64 INF = 1e12;
class Solution {
 public:
  i64 minimumWeight(int n,
                    std::vector<std::vector<int>>& edges,
                    int src1,
                    int src2,
                    int dest) {
    // Interesting. Seems like a Shortest Path/SSSP problem outright.
    // But the shortest path from src1 to dest AND the shortest path from src2
    // to dest may not be the minimum weighted subgraph.
    //
    // Intuitively, we want as much overlap between the shortest path as much
    // as possible, to reduce the weight of the resultant subgraph.
    // Multiple Dijkstra's?
    // - Dijkstra from src1 to dest
    // - Dijkstra from src2 to dest
    // - Dijkstra from src1 -> dest THROUGH src2, i.e., Dijkstra from src1
    //   to src2 and then dest. Vice versa.
    // LOL. Update on 28 March. Where did this "Intuitively" come from??
    //
    // Note that the distance array returned by Dijkstra is the shortest path
    // spanning tree, where dist[i] is the shortest path from src to node i.
    // As such, if we have the respective distances array from src1 and src2,
    // we can determine the shortest path to reach an arbitrary node i from
    // both src1 and src2.
    // Then, combine that with the shortest path to reach dest from the
    // arbitrary node i, we get the minimum weighted subgraph.
    // Note that to get the shortest path from node i to dest, we can instead
    // reverse the edges to find the shortest path from dest to all nodes.
    //
    // Anyways. The intuition is actually correct. But the follow-up to the
    // intuition is not.
    // Note that to find the best overlapping path, we first need to find a
    // path to a common node i from src1 and src2. This gives us sum1 + sum2,
    // (note that there wont be double counting of edges, since src1 != src2).
    // From that node i onwards, we take the shortest path from i to dest.
    // This is really similar to Floyd-Warshalls tbh.
    std::vector<std::vector<std::pair<int, int>>> G(n);
    std::vector<std::vector<std::pair<int, int>>> GRev(n);
    for (const auto& edge : edges) {
      const int from = edge[0];
      const int to = edge[1];
      const int weight = edge[2];
      G[from].emplace_back(to, weight);
      GRev[to].emplace_back(from, weight);
    }

    auto dijkstra = [n](const auto& adj, int src) -> std::vector<i64> {
      std::vector<i64> distance(n, INF);
      std::priority_queue<std::pair<i64, int>, std::vector<std::pair<i64, int>>,
                          std::greater<>>
          minHeap;
      minHeap.emplace(0LL, src);
      distance[src] = 0LL;
      while (!minHeap.empty()) {
        auto [dist, curr] = minHeap.top();
        minHeap.pop();
        if (dist > distance[curr]) {
          continue;  // pruning step for outdated nodes in the frontier.
        }

        for (auto [next, weight] : adj[curr]) {
          if (distance[curr] + weight >= distance[next]) {
            continue;
          }

          distance[next] = distance[curr] + weight;
          minHeap.emplace(distance[next], next);
        }
      }

      return distance;
    };

    auto distSrc1 = dijkstra(G, src1);
    auto distSrc2 = dijkstra(G, src2);
    auto distDest = dijkstra(GRev, dest);

    i64 result = INF;
    for (auto [s1, s2, d] :
         std::ranges::views::zip(distSrc1, distSrc2, distDest)) {
      result = std::min(result, s1 + s2 + d);
    }

    if (result == INF) {
      return -1;
    }
    return result;
  }
};
