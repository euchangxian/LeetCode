#include <queue>
#include <vector>

class Solution {
  int distanceFromOrigin(const std::vector<int>& p) {
    return (p[0] * p[0]) + (p[1] * p[1]);
  }

 public:
  std::vector<std::vector<int>> kClosest(std::vector<std::vector<int>>& points,
                                         int k) {
    int n = points.size();

    // Pre-compute distances
    std::vector<int> distances(n);
    for (int i = 0; i < n; ++i) {
      distances[i] = distanceFromOrigin(points[i]);
    }

    auto less = [&distances](int i, int j) {
      return distances[i] < distances[j];
    };

    // Maintains the k closest points to the origin. If a new point has
    // a smaller distance than the top of the heap, then pop and replace.
    std::priority_queue<int, std::vector<int>, decltype(less)> maxHeap(less);
    for (int i = 0; i < n; ++i) {
      maxHeap.push(i);

      if (maxHeap.size() > k) {
        maxHeap.pop();
      }
    }

    std::vector<std::vector<int>> result;
    result.reserve(k);
    while (!maxHeap.empty()) {
      result.push_back(points[maxHeap.top()]);
      maxHeap.pop();
    }
    return result;
  }
};
