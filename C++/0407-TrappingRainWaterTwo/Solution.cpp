#include <algorithm>
#include <functional>
#include <queue>
#include <tuple>
#include <vector>

constexpr std::array<std::array<int, 2>, 4> directions{{
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0},
}};

class Solution {
 public:
  int trapRainWater(std::vector<std::vector<int>>& heightMap) {
    int rows = heightMap.size();
    int cols = heightMap[0].size();

    if (rows < 3 || cols < 3) {
      return 0;  // Edge cells cannot trap water
    }

    // Tuple of {height, row, col}. Use a minHeap to pop lower heights first
    std::priority_queue<std::tuple<int, int, int>,
                        std::vector<std::tuple<int, int, int>>, std::greater<>>
        minHeap;
    std::vector<std::vector<bool>> visited(rows,
                                           std::vector<bool>(cols, false));

    // Add top and bottom edge cells
    for (int c = 0; c < cols; ++c) {
      minHeap.emplace(heightMap[0][c], 0, c);
      visited[0][c] = true;

      minHeap.emplace(heightMap[rows - 1][c], rows - 1, c);
      visited[rows - 1][c] = true;
    }

    // Add left and right edge cells
    for (int r = 1; r < rows - 1; ++r) {
      minHeap.emplace(heightMap[r][0], r, 0);
      visited[r][0] = true;

      minHeap.emplace(heightMap[r][cols - 1], r, cols - 1);
      visited[r][cols - 1] = true;
    }

    // Starting from lower-height cells, check if its adjacent, inner cells
    // are of lower height.
    // Due to the order of traversal, if the neighbouring cell is of lower
    // height, it can trap water.
    int result = 0;
    while (!minHeap.empty()) {
      auto [height, r, c] = minHeap.top();
      minHeap.pop();

      for (const auto [dr, dc] : directions) {
        int nr = r + dr;
        int nc = c + dc;

        if (nr < 0 || nc < 0 || nr >= rows || nc >= cols || visited[nr][nc]) {
          continue;
        }

        visited[nr][nc] = true;
        // For a neighbouring cell, there are two scenarios:
        // 1. The neighbouring cell has a lower height than the current cell.
        //    This means that the neighbouring cell can trap water of volume
        //    height - heightMap[nr][nc].
        //    Thus, we push the cell into the heap with the current cell's
        //    height
        // 2. The neighbouring cell has a equal/greater height.
        //    Thus, the neighbouring cell cannot trap water. The current
        //    cell's height will not be relevant to inner cells.
        result += std::max(0, height - heightMap[nr][nc]);
        minHeap.emplace(std::max(height, heightMap[nr][nc]), nr, nc);
      }
    }

    return result;
  }
};
