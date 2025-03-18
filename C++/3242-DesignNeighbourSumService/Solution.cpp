#include <cstddef>
#include <utility>
#include <vector>

/**
 * n x n 2D grid with distinct elements in the range [0..n^2 - 1]
 * Since we are indexing by the value, we need to map the value to their
 * indices. This takes O(n^2) time in the initialization.
 *
 * From here, there are two choices: precompute the adjacent/diagonal sum, or
 * compute on demand. Since two grids need to be stored, the tradeoffs in space
 * is minimal, and so is the tradeoffs in time.
 */
class NeighborSum {
 public:
  NeighborSum(std::vector<std::vector<int>>& grid)
      : grid(grid), indices(grid.size() * grid.size()) {
    for (std::size_t i = 0; i < grid.size(); ++i) {
      for (std::size_t j = 0; j < grid.size(); ++j) {
        indices[grid[i][j]] = std::make_pair(i, j);
      }
    }
  }

  int adjacentSum(int value) { return neighbourSum(value, adjacent); }

  int diagonalSum(int value) { return neighbourSum(value, diagonal); }

 private:
  static constexpr std::array<std::pair<int, int>, 4> adjacent = {
      {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}};

  static constexpr std::array<std::pair<int, int>, 4> diagonal = {
      {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}}};

  const std::vector<std::vector<int>> grid;
  std::vector<std::pair<int, int>> indices;

  int neighbourSum(int value,
                   const std::array<std::pair<int, int>, 4>& directions) {
    const auto& [r, c] = indices[value];

    int sum = 0;
    for (const auto& [dr, dc] : directions) {
      const int nr = r + dr;
      const int nc = c + dc;

      if (nr < 0 || nc < 0 || nr >= grid.size() || nc >= grid.size()) {
        continue;
      }
      sum += grid[nr][nc];
    }
    return sum;
  }
};

/**
 * Your NeighborSum object will be instantiated and called as such:
 * NeighborSum* obj = new NeighborSum(grid);
 * int param_1 = obj->adjacentSum(value);
 * int param_2 = obj->diagonalSum(value);
 */
