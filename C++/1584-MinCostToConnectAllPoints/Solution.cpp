#include <algorithm>
#include <climits>
#include <vector>

class Solution {
 public:
  int minCostConnectPoints(const std::vector<std::vector<int>>& points) {
    // Each point has an edge to every other point, making it a clique
    // Prim's seem more suitable for Complete Graphs.
    // Prim's: Add nodes to a minHeap, ordered by the weight of the edges
    // Pop the least cost one.
    const std::size_t n = points.size();

    // There is technically an optimization, to set the distance of nodes
    // already in the MST to INT_MAX.
    std::vector<bool> seen(n, false);
    std::vector<int> distance(n, INT_MAX);
    distance[0] = 0;

    int minCost = 0;
    // using '_' in C++ does not have any semantic meaning. I only used it to
    // indicate that I do not need this variable, only to loop.
    for (int _ = 0; _ < n; ++_) {
      // pick the minDistance
      int minIdx = 0;
      int minDistance = INT_MAX;
      for (int i = 0; i < n; ++i) {
        if (!seen[i] && distance[i] < minDistance) {
          minIdx = i;
          minDistance = distance[i];
        }
      }

      minCost += minDistance;
      seen[minIdx] = true;
      for (int i = 0; i < n; ++i) {
        if (seen[i]) {
          continue;
        }

        distance[i] = std::min(
            distance[i], manhanttanDist(points[minIdx][0], points[minIdx][1],
                                        points[i][0], points[i][1]));
      }
    }
    return minCost;
  }

 private:
  int manhanttanDist(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
  }
};
