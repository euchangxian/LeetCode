#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class Solution {
  int distanceFromOrigin(vector<int> const &p) {
    return (p[0] * p[0]) + (p[1] * p[1]);
  }

public:
  vector<vector<int>> kClosest(vector<vector<int>> &points, int k) {
    int n = points.size();

    // Pre-compute distances
    vector<int> distances(n);
    for (int i = 0; i < n; ++i) {
      distances[i] = distanceFromOrigin(points[i]);
    }

    auto less = [&distances](int i, int j) {
      return distances[i] < distances[j];
    };

    // Maintains the k closest points to the origin. If a new point has
    // a smaller distance than the top of the heap, then pop and replace.
    priority_queue<int, vector<int>, decltype(less)> maxHeap(less);
    for (int i = 0; i < n; ++i) {
      maxHeap.push(i);

      if (maxHeap.size() > k) {
        maxHeap.pop();
      }
    }

    vector<vector<int>> result;
    result.reserve(k);
    while (!maxHeap.empty()) {
      result.push_back(points[maxHeap.top()]);
      maxHeap.pop();
    }
    return result;
  }
};
