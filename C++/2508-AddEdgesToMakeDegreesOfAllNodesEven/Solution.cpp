#include <cstdint>
#include <unordered_set>
#include <vector>

class Solution {
 public:
  bool isPossible(int n, std::vector<std::vector<int>>& edges) {
    // Adding an edge will increase the degree of two nodes.
    // Since we can only add 0, 1, or 2 edges, the number of odd-degree nodes
    // must be either 0, 2 or 4. Anything else will not be possible.
    // Also, repeated edges cannot be added. There cannot be two edges between
    // the same node.
    // Lazy to deal with 1-indexed n
    std::vector<int32_t> degree(n + 1);
    std::vector<std::unordered_set<int32_t>> hasEdge(n + 1);

    for (const auto& edge : edges) {
      ++degree[edge[0]];
      ++degree[edge[1]];

      hasEdge[edge[0]].emplace(edge[1]);
    }

    // Count the number of odd-degree nodes
    constexpr int32_t maxOdds = 4;
    constexpr int32_t isOdd = 1;
    std::vector<int32_t> oddDegrees;
    oddDegrees.reserve(4);
    for (size_t i = 1; i <= n; ++i) {
      if (degree[i] & isOdd) {
        oddDegrees.push_back(i);
      }

      if (oddDegrees.size() > maxOdds) {
        // Early return
        return false;
      }
    }

    // There are three different cases:
    // 1. numOdd is 0, trivially return true. no extra edges needed.
    // 2. numOdd is either 2 or 4. Check that the oddDegree nodes does not
    //    already have existing edges. between each of them.
    // 3. Otherwise, return false.
    if (oddDegrees.size() == 0) {
      return true;
    }

    if (oddDegrees.size() == 2) {
      // Check that edges can be added between the two node.
      const int32_t a = oddDegrees[0];
      const int32_t b = oddDegrees[1];

      // Only hasEdge[a][b] need to be checked, and not hasEdge[b][a]. This is
      // because we added both cases in the processing step.
      if (canConnect(hasEdge, a, b)) {
        return true;
      }

      // EDGE CASE.......
      // Even if there is an edge between the two odd-degree nodes, we can still
      // find an even-degree node that does not yet have edges with these two.
      // Connecting both edges to it will result in all-even degree nodes...
      for (size_t i = 1; i <= n; ++i) {
        if (i == a || i == b) {
          continue;
        }

        if (canConnect(hasEdge, i, a) && canConnect(hasEdge, i, b)) {
          return true;
        }
      }
    }

    if (oddDegrees.size() == 4) {
      const int32_t a = oddDegrees[0];
      const int32_t b = oddDegrees[1];
      const int32_t c = oddDegrees[2];
      const int32_t d = oddDegrees[3];

      // Check all combinations: whether two edges can be added,
      // a -- b and c -- d
      // a -- c and b -- d
      // a -- d and b -- c
      return (canConnect(hasEdge, a, b) && canConnect(hasEdge, c, d)) ||
             (canConnect(hasEdge, a, c) && canConnect(hasEdge, b, d)) ||
             (canConnect(hasEdge, a, d) && canConnect(hasEdge, b, c));
    }

    return false;
  }

 private:
  bool canConnect(const std::vector<std::unordered_set<int32_t>>& hasEdge,
                  const int32_t a,
                  const int32_t b) {
    return hasEdge[a].count(b) == 0 && hasEdge[b].count(a) == 0;
  }
};
