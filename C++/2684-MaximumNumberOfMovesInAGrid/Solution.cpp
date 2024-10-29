#include <algorithm>
#include <array>
#include <cstddef>
#include <vector>

using namespace std;
class Solution {
 private:
  static constexpr std::array<std::pair<int, int>, 3> directions{
      {{-1, 1}, {0, 1}, {1, 1}}};

 public:
  int maxMoves(vector<vector<int>>& grid) {
    // Can move diagonally up/down, and move right, as long as the value of the
    // destination cell is strictly greater.
    // No moving leftwards.
    //
    // Choose any cell in the FIRST column.
    // Want: maximum number of moves.
    // Note: Only can move rightwards. Maximum number of moves is limited to
    // the number of columns.
    //
    // A cell has at most 3 neighbours (to its left).
    // dp[i][j] represents the maximum number of moves taken to reach
    // cell (i, j)
    // pseduocode:
    // for row in rows:
    //   for col in cols:
    //     update(neighbours of cell to the right)
    //     update(result)
    const size_t rows = grid.size();
    const size_t cols = grid[0].size();

    int result = 0;
    std::vector<std::vector<int>> dp(rows, std::vector<int>(cols, 0));

    // NOTE THE ORDER OF ITERATION
    // Iterate in column-order. This is so that cells are not wrongly processed
    // as unreachable.
    // E.g.,
    // 9 8 9
    // 1 1 1
    // 1 1 1
    //
    // If row-order, then we would mark (r1, c1) = 8 as unreachable,
    // consequently, (r2, c2) would be unreachable. Thus, 0 would be wrongly
    // returned.
    for (size_t c = 0; c < cols - 1; ++c) {
      for (size_t r = 0; r < rows; ++r) {
        if (c > 0 && dp[r][c] == 0) {
          // if not the first column, and the number of moves is still 0, then
          // it means that the cell was not reachable.
          continue;
        }

        // for each neighbour, check if strictly greater. if so, update.
        for (const auto& [dr, dc] : directions) {
          int nr = r + dr;
          int nc = c + dc;

          if (nr < 0 || nc < 0 || nr >= rows || nc >= cols ||
              grid[nr][nc] <= grid[r][c]) {
            continue;
          }

          dp[nr][nc] = std::max(dp[nr][nc], 1 + dp[r][c]);
          result = std::max(result, dp[nr][nc]);
        }
      }
    }

    return result;
  }
};
