#include <algorithm>
#include <functional>
#include <vector>

class Solution {
 public:
  std::vector<std::vector<int>> rotateGrid(std::vector<std::vector<int>>& grid,
                                           int k) {
    // m*n grid, where both m and n are even.
    // Grids have layers.
    // Rotate each layer in the matrix k times, anti-clockwise.
    const auto m = static_cast<int>(grid.size());
    const auto n = static_cast<int>(grid[0].size());
    const auto layers = std::min(m / 2, n / 2);

    std::vector<std::reference_wrapper<int>> points;
    std::vector<int> vals;
    vals.reserve(2 * (m + n));
    for (auto layer = 0; layer < layers; ++layer) {
      auto top = layer;
      auto left = layer;
      auto bottom = m - layer - 1;
      auto right = n - layer - 1;

      // top row (left-to-right)
      for (auto c = left; c < right; ++c) {
        auto& cell = grid[top][c];
        points.emplace_back(cell);
        vals.push_back(cell);
      }

      // right column (top-to-bottom)
      for (auto r = top; r < bottom; ++r) {
        auto& cell = grid[r][right];
        points.emplace_back(cell);
        vals.push_back(cell);
      }

      // bottom row (right-to-left)
      for (auto c = right; c > left; --c) {
        auto& cell = grid[bottom][c];
        points.emplace_back(cell);
        vals.push_back(cell);
      }

      // left column (bottom to top)
      for (auto r = bottom; r > top; --r) {
        auto& cell = grid[r][left];
        points.emplace_back(cell);
        vals.push_back(cell);
      }

      const auto perimeter = static_cast<int>(points.size());
      const auto rotations = k % perimeter;
      for (auto i = 0; i < perimeter; ++i) {
        // points[i] = vals[(i + perimeter - rotations) % perimeter];
        points[i].get() = vals[(i + rotations) % perimeter];
      }
      points.clear();
      vals.clear();
    }
    return grid;
  }
};
