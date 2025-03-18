#include <vector>

class Solution {
 public:
  std::vector<std::vector<int>> construct2DArray(std::vector<int>& original,
                                                 int m,
                                                 int n) {
    if (original.size() != m * n) {
      return {};
    }

    std::vector<std::vector<int>> grid(m, std::vector<int>(n, 0));
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        int mappedIdx = i * n + j;
        grid[i][j] = original[mappedIdx];
      }
    }
    return grid;
  }
};
