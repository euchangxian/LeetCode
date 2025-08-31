#include <algorithm>
#include <array>
#include <limits>
#include <vector>

class Solution {
 public:
  std::vector<int> shortestDistanceColor(
      std::vector<int>& colors,
      std::vector<std::vector<int>>& queries) {
    // We can preprocess in another way to get
    // left[c][i]: nearest c to the left of i,
    // right[c][i]: nearest c to the right of i.
    // Can be done y keeping track of the last index we saw in both the forward
    // and backward direction.
    const auto n = static_cast<int>(colors.size());

    std::array<std::vector<int>, 4> left;
    left[1] = left[2] = left[3] = std::vector<int>(n);
    std::array<int, 4> lastSeen{{-1, -1, -1, -1}};
    for (int i = 0; i < n; ++i) {
      lastSeen[colors[i]] = i;
      for (int c = 1; c <= 3; ++c) {
        left[c][i] = lastSeen[c];
      }
    }

    std::array<std::vector<int>, 4> right;
    right[1] = right[2] = right[3] = std::vector<int>(n);
    lastSeen = {n, n, n, n};
    for (int i = n - 1; i >= 0; --i) {
      lastSeen[colors[i]] = i;
      for (int c = 1; c <= 3; ++c) {
        right[c][i] = lastSeen[c];
      }
    }

    std::vector<int> result;
    result.reserve(n);
    for (const auto& query : queries) {
      int i = query[0];
      int c = query[1];

      int distLeft = std::numeric_limits<int>::max();
      if (left[c][i] != -1) {
        distLeft = i - left[c][i];
      }

      int distRight = std::numeric_limits<int>::max();
      if (right[c][i] != n) {
        distRight = right[c][i] - i;
      }

      auto dist = std::min(distLeft, distRight);
      result.push_back(dist == std::numeric_limits<int>::max() ? -1 : dist);
    }
    return result;
  }

  std::vector<int> shortestDistanceColorBinarySearch(
      std::vector<int>& colors,
      std::vector<std::vector<int>>& queries) {
    // colors[i] = 1 | 2 | 3
    // queries[i] = {i, c}
    // For each query, return the shortest distance between the index i and
    // the target color c.
    //
    // Seems like binary search.
    // Preprocess to indices[1] = {i, ...}, i.e., index of colors[i] = 1
    const auto n = static_cast<int>(colors.size());

    std::array<std::vector<int>, 3 + 1> colorIndices{};
    for (int i = 0; i < n; ++i) {
      colorIndices[colors[i]].push_back(i);
    }

    std::vector<int> result;
    result.reserve(n);
    for (const auto& query : queries) {
      int i = query[0];
      int c = query[1];

      const auto& indices = colorIndices[c];

      auto it = std::lower_bound(indices.begin(), indices.end(), i);
      int dist = std::numeric_limits<int>::max();
      if (it != indices.end()) {
        dist = std::min(dist, *it - i);
      }

      if (it != indices.begin()) {
        dist = std::min(dist, i - *(it - 1));
      }

      result.push_back(dist == std::numeric_limits<int>::max() ? -1 : dist);
    }
    return result;
  }
};
