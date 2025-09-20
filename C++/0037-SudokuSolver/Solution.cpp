#include <vector>

constexpr int N = 9;

class Solution {
 public:
  void solveSudoku(std::vector<std::vector<char>>& board) {
    // Each digit [1..9] must occur exactly once in each row.
    // Each digit [1..9] must occur exactly once in each column.
    // Each digit [1..9] must occur exactly once in each 3x3 sub-grid.
    //
    // Backtracking. But how do we prune?
    auto canPlace = [&](int i, int j, char val) {
      for (int r = 0; r < N; ++r) {
        if (board[r][j] == val) {
          return false;
        }
      }

      for (int c = 0; c < N; ++c) {
        if (board[i][c] == val) {
          return false;
        }
      }

      int row = i - (i % 3);
      int col = j - (j % 3);
      for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
          if (board[row + r][col + c] == val) {
            return false;
          }
        }
      }
      return true;
    };

    auto dfs = [&](this auto&& dfs, int i, int j) {
      if (i == N) {
        return true;
      }
      if (j == N) {
        return dfs(i + 1, 0);
      }

      if (board[i][j] != '.') {
        return dfs(i, j + 1);
      }

      for (char c = '1'; c <= '9'; ++c) {
        if (canPlace(i, j, c)) {
          board[i][j] = c;
          if (dfs(i, j + 1)) {
            return true;
          }
          board[i][j] = '.';
        }
      }
      return false;
    };

    dfs(0, 0);
  }
};
