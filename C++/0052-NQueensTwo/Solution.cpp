#include <bitset>

class Solution {
 public:
  int totalNQueens(int n) {
    // See 51. NQueens I
    std::bitset<30> row{}, ld{}, rd{};
    int result = 0;
    dfs(n, 0, row, ld, rd, result);
    return result;
  }

 private:
  void dfs(const int n,
           int c,  // column
           std::bitset<30>& row,
           std::bitset<30>& ld,
           std::bitset<30>& rd,
           int& result) {
    if (c == n) {
      ++result;
      return;
    }

    // try all possible rows
    for (int r = 0; r < n; ++r) {
      if (!row[r] && !ld[r - c + n - 1] && !rd[r + c]) {
        row[r] = ld[r - c + n - 1] = rd[r + c] = true;
        dfs(n, c + 1, row, ld, rd, result);
        row[r] = ld[r - c + n - 1] = rd[r + c] = false;
      }
    }
  }
};
