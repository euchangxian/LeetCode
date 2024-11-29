#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  int maximalNetworkRank(int n, std::vector<std::vector<int>>& roads) {
    // seems to be counting the degree. Pick the Max degree node.
    // Then, for the second max, if there is a tie, pick the one that
    // is not connected to the max.

    // Adjacency matrix for fast connection lookup.
    std::vector<std::vector<char>> connected(n, std::vector<char>(n, false));
    std::vector<int> degree(n, 0);
    for (const auto& edge : roads) {
      const int from = edge[0];
      const int to = edge[1];

      ++degree[from];
      ++degree[to];

      connected[from][to] = true;
      connected[to][from] = true;
    }

    int maxRank = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        int rank = degree[i] + degree[j] - connected[i][j];
        maxRank = std::max(maxRank, rank);
      }
    }

    return maxRank;
  }
};
