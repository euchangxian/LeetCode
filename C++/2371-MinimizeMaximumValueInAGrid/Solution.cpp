#include <algorithm>
#include <cstddef>
#include <tuple>
#include <vector>

class Solution {
 public:
  std::vector<std::vector<int>> minScore(std::vector<std::vector<int>>& grid) {
    // To replace integers in the grid such that the relative order across rows
    // and columns remains the same, but the maximum number in the matrix is
    // as small as possible.
    // Does feel a little like topological sort. Something like
    // LC 2392.Build A Matrix With Conditions
    // We can possibly model the grid cells as nodes, where a node has a
    // directed edge to another node if it belongs to the same row/column, and
    // has a larger value.
    // i.e., (0, 0) = 1  ---> (0, 4) = 2
    // This would allow us to traverse this dependency graph and minus the value
    // of each node such that it is +1 of the previous node.
    // Feels kinda difficult and inefficient to implement though. Using Kahn's
    // algorithm would mean that each cell would have up to
    // (m-1) + (n-1) neighbours. Kinda expensive!
    // Can we do better?? What about using an adjacency matrix? IDTS. adjList
    // would not be close to a complete graph to make the overhead worth.
    // Lets just try it out.
    // WAIT a minute. "grid" consists of distinct integers. Could this be
    // useful?
    // Starting from cells with values 2 (since 1 cannot be reduced further),
    // if the row/column of the cell has no '1's, then we can reduce the value
    // to 1.
    // Then, from cells with values 3, we can reduce it to 2 if there are no
    // 2s in the same row/column, 1s if there are no 2s AND 1s in the same
    // row/column.
    // And so on.
    // Though grid[i][j] <= 10^9, so i guess this is not feasible.
    // BUT instead of iterating through values 1 through 10^9, what about having
    // the same concept, but iterate through the smallest to largest value?
    // This exploits the uniqueness of values in the grid.
    // I.e., collect all m * n indices, sort based on their values.
    // Hm. How to efficiently determine the value that a cell can be reduced to?
    // What about maintaining the max-so-far of each row/column!!
    const std::size_t m = grid.size();
    const std::size_t n = grid[0].size();

    // {value, row, col}
    std::vector<std::tuple<int, int, int>> cells;
    cells.reserve(m * n);
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        cells.emplace_back(grid[i][j], i, j);
      }
    }

    // Remember: distinct cell values.
    std::sort(cells.begin(), cells.end());

    // 1 <= grid[i][j] <= 10^9 => 0 is invalid, and the cell can be reduced to
    // 1.
    std::vector<int> rowMax(m, 0);
    std::vector<int> colMax(n, 0);

    // for each cell in the sorted order, try to reduce it to 1 + row/colMax
    for (int i = 0; i < m * n; ++i) {
      auto [val, r, c] = cells[i];

      // if the current value is greater than BOTH row max and col max, reduce
      // it to max(row, col) + 1
      if (val > rowMax[r] && val > colMax[c]) {
        grid[r][c] = std::max(rowMax[r], colMax[c]) + 1;
        rowMax[r] = grid[r][c];
        colMax[c] = grid[r][c];
      }
    }

    return grid;
  }
};
