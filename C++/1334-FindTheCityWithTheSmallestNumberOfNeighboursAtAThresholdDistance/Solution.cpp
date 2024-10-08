#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
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
  int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
    // dp[i][j] represents the shortest distance from i to j
    vector<vector<int>> dp(n, vector<int>(n, INT_MAX));

    for (int i = 0; i < n; ++i) {
      dp[i][i] = 0;  // distance to self is zero
    }

    for (const auto& edge : edges) {
      int from = edge[0];
      int to = edge[1];
      int dist = edge[2];
      dp[from][to] = dist;
      dp[to][from] = dist;
    }

    for (int k = 0; k < n; ++k) {
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          if (dp[i][k] == INT_MAX || dp[k][j] == INT_MAX) {
            continue;
          }
          dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
        }
      }
    }

    int city = 0;
    int minReachable = INT_MAX;
    for (int i = 0; i < n; ++i) {
      int currentCount = 0;
      for (int j = 0; j < n; ++j) {
        if (dp[i][j] <= distanceThreshold) {
          ++currentCount;
        }
      }
      if (currentCount <= minReachable) {
        city = i;
        minReachable = currentCount;
      }
    }

    return city;
  }
};
