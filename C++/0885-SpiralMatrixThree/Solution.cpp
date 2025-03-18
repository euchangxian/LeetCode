#include <vector>

class Solution {
 public:
  std::vector<std::vector<int>> spiralMatrixIII(int rows,
                                                int cols,
                                                int rStart,
                                                int cStart) {
    std::vector<std::vector<int>> visited;
    visited.reserve(rows * cols);
    visited.push_back({rStart, cStart});

    // Right, Down, Left, Up
    // Determined by iter
    std::vector<std::pair<int, int>> directions = {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    int iter = 0;
    while (true) {
      if (visited.size() == rows * cols) {
        break;
      }

      int stride = (iter / 2) + 1;
      const auto [r, c] = directions[iter % 4];
      for (int i = 0; i < stride; ++i) {
        rStart += r;
        cStart += c;

        if (rStart >= 0 && rStart < rows && cStart >= 0 && cStart < cols) {
          visited.push_back({rStart, cStart});
        }
      }

      ++iter;
    }

    return visited;
  }
};
