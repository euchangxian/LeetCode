#include <algorithm>
#include <vector>

enum Cell : char {
  Wall = 'W',
  Enemy = 'E',
  Empty = '0',
};

class Solution {
 public:
  int maxKilledEnemies(std::vector<std::vector<char>>& grid) {
    // O(MN) time to traverse empty cells.
    // For each empty cell: O(4 * max{M, N})
    // NAIVE: O(MN * 4MAX(M, N)).
    int m = grid.size();
    int n = grid[0].size();

    // for-each empty-cell
    int rowHits = 0;
    std::vector<int> colHits(n, 0);

    int result = 0;
    for (int row = 0; row < m; ++row) {
      for (int col = 0; col < n; ++col) {
        // scan column to the right, if starting a new row,
        // or a wall was hit previously.
        if (col == 0 || grid[row][col - 1] == Cell::Wall) {
          rowHits = 0;
          for (int k = col; k < n; ++k) {
            if (grid[row][k] == Cell::Wall) {
              break;
            }

            rowHits += grid[row][k] == Cell::Enemy;
          }
        }

        // scan row downwards if starting a new col
        if (row == 0 || grid[row - 1][col] == Cell::Wall) {
          colHits[col] = 0;
          for (int k = row; k < m; ++k) {
            if (grid[k][col] == Cell::Wall) {
              break;
            }

            colHits[col] += grid[k][col] == Cell::Enemy;
          }
        }

        if (grid[row][col] == Cell::Empty) {
          result = std::max(result, rowHits + colHits[col]);
        }
      }
    }
    // return max.
    return result;
  }
};
