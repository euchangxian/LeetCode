#include <bitset>
#include <string>
#include <vector>

class Solution {
 public:
  std::vector<std::vector<std::string>> solveNQueens(int n) {
    // Return all distinct solutions.
    // "Harder" variant.
    // n <= 9
    //
    // 1. Naive brute-force is to enumerate all combinations of the 9*9 board:
    //    81C9 ~= 260x10^9. Absurdly long.
    // 2. Realise each column can only contain one queen. 9^9 ~= 387M
    //    Much better, likely to TLE still.
    // 3. Similarly, each row can only contain one queen. Thus, no two queens
    //    can share the same column or row.
    //    This reduces the problem into finding permutations of 9! row
    //    positions, checking diagonals to determine if the permutation is
    //    valid.
    //    9! ~= 362K
    // 4. Now, knowing two queens also cannot share diagonal lines, i.e.,
    //    if queen A is at (i, j), queen B is at (k, l), i != k, j != l, then
    //    they attack each other diagonally if abs(i-k) == abs(j-l).
    //    This formula means that the vertical and horizontal distances between
    //    the two Queens are equal.

    // row[i] indicate that a Queen is in the row.
    // diagonals where
    // ld represents diagonals starting from the bottom-left, to the top-right,
    // rd represents diagonals starting from the bottom-right, to the top-left.
    // 2 * n - 1 left/right diagonals.
    // Given that abs(i-k) == abs(j-l) has two cases:
    // i+k = j+l
    // i-k = j-l, where this could possibly be negative, we add an offset n-1:
    // i+k + n-1 = j+l + n-1, and
    // i-k + n-1 = j-l + n-1
    // Thus, if a Queen is placed on cell (r, c), we flag
    // ld[r-c + n-1] and rd[r+c] to prevent these two diagonals from being used.
    std::bitset<30> row{}, ld{}, rd{};

    std::vector<std::string> board(n, std::string(n, '.'));
    std::vector<std::vector<std::string>> result;
    dfs(n, 0, row, ld, rd, board, result);
    return result;
  }

 private:
  void dfs(const int n,
           int c,  // column
           std::bitset<30>& row,
           std::bitset<30>& ld,
           std::bitset<30>& rd,
           std::vector<std::string>& board,
           std::vector<std::vector<std::string>>& result) {
    if (c == n) {
      result.push_back(board);
      return;
    }

    // try all possible rows
    for (int r = 0; r < n; ++r) {
      if (!row[r] && !ld[r - c + n - 1] && !rd[r + c]) {
        row[r] = ld[r - c + n - 1] = rd[r + c] = true;
        board[r][c] = 'Q';
        dfs(n, c + 1, row, ld, rd, board, result);
        board[r][c] = '.';
        row[r] = ld[r - c + n - 1] = rd[r + c] = false;
      }
    }
  }
};
