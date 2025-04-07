#include <algorithm>
#include <array>
#include <vector>

constexpr int MAX_N = 100;
constexpr int INF = 0x3F3F3F3F;

class Solution {
 public:
  // Floyd Warshall's All Pairs Shortest Paths
  // Optimal Substructure: If a shortest path from i to j goes through an
  // intermediate vertex k, then the path i to k and k to j must also be
  // shortest paths.
  //
  // dist(i, j, k) represents the shortest path from vertex i to j using
  // vertices {0, 1, ..., k} as intermediate vertices.
  //
  // Recursive Relation:
  // dist(i, j, k) = min(dist(i, j, k-1), dist(i, k, k-1) + dist(k, j, k-1))
  //
  // This means that the shortest path from i to j using vertices up to k is the
  // minimum between the path that does not goes through k, dist(i, j, k - 1)
  // and the path that goes through k, dist(i, k, k - 1) + dist(k, j, k - 1).
  int findTheCity(int n,
                  std::vector<std::vector<int>>& edges,
                  int distanceThreshold) {
    // dp[i][j] represents the shortest distance from i to j
    std::array<std::array<int, MAX_N + 1>, MAX_N + 1> dp;
    std::memset(dp.data(), INF, sizeof(dp));

    for (const auto& edge : edges) {
      int from = edge[0];
      int to = edge[1];
      int dist = edge[2];
      dp[from][to] = dp[to][from] = dist;
    }

    for (int k = 0; k < n; ++k) {
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          dp[i][j] = std::min(dp[i][j], dp[i][k] + dp[k][j]);
        }
      }
    }

    int city = 0;
    int minReachable = INF;
    for (int i = 0; i < n; ++i) {
      int count = 0;
      for (int j = 0; j < n; ++j) {
        if (i != j && dp[i][j] <= distanceThreshold) {
          ++count;
        }
      }

      if (count <= minReachable) {
        minReachable = count;
        city = i;
      }
    }

    return city;
  }
};
