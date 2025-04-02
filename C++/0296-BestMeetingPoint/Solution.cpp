#include <vector>

class Solution {
 public:
  int minTotalDistance(std::vector<std::vector<int>>& grid) {
    // A little relaxed variant of 317.Shortest Distance From All Buildings.
    // This one doesnt have obstacles.
    // Hm. Not necessarily relaxed. Each meeting point can be located at
    // a friend cell.
    // Consider a 1-dimensional line.
    // Then, consider an arbitrary point x, with l friends on the left, and r
    // friends on the right.
    // WLOG, moving this point 1 unit leftwards will increase the total distance
    // by r+1 units.
    // Therefore, we can conclude that the total distance is optimal when there
    // are an equal number of friends on the left and the right.
    // i.e., Median.
    const int m = grid.size();
    const int n = grid[0].size();

    std::vector<int> dimR, dimC;

    // NOTE: Observe that we are iterating over rows in ascending order already.
    // Thus, we do not have to sort.
    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        if (grid[r][c] == 1) {
          dimR.push_back(r);
        }
      }
    }

    // we iterate over ascending columns. While this has a better theoretical
    // time complexity, it may perform worse due to cache misses.
    for (int c = 0; c < n; ++c) {
      for (int r = 0; r < m; ++r) {
        if (grid[r][c] == 1) {
          dimC.push_back(c);
        }
      }
    }

    return minDistance1D(dimR) + minDistance1D(dimC);
  }

 private:
  int minDistance1D(std::vector<int>& points) {
    int dist = 0;

    int i = 0;
    int j = points.size() - 1;
    while (i < j) {
      // NOTE: This is equivalent to calculating:
      // (points[j] - median) + (median - points[i]) == points[j] - points[i]
      // Exploits the sorted-ness of the input.
      dist += points[j--] - points[i++];
    }
    return dist;
  }
};
