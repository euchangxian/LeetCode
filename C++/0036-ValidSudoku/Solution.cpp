#include <vector>

using namespace std;
class Solution {
 private:
  bool isRowValid(vector<vector<char>> const& board, int row) {
    vector<bool> present = vector<bool>(9, false);
    for (char num : board[row]) {
      if (num == '.') {
        continue;
      }
      if (present[num - '0']) {
        return false;
      }
      present[num - '0'] = true;
    }
    return true;
  }

  bool isColValid(vector<vector<char>> const& board, int col) {
    vector<bool> present = vector<bool>(9, false);
    for (auto row : board) {
      if (row[col] == '.') {
        continue;
      }
      if (present[row[col] - '0']) {
        return false;
      }
      present[row[col] - '0'] = true;
    }
    return true;
  }

  bool isBoxValid(vector<vector<char>> const& board, int row, int col) {
    // no bounds check. assume inputs are correct.
    vector<bool> present = vector<bool>(9, false);
    for (int i = row; i < row + 3; ++i) {
      for (int j = col; j < col + 3; ++j) {
        if (board[i][j] == '.') {
          continue;
        }
        if (present[board[i][j] - '0']) {
          return false;
        }
        present[board[i][j] - '0'] = true;
      }
    }
    return true;
  }

 public:
  bool isValidSudoku(vector<vector<char>>& board) {
    for (int i = 0; i < 9; i += 3) {
      for (int j = 0; j < 9; j += 3) {
        bool boxResult = isBoxValid(board, i, j);
        if (!boxResult) {
          return false;
        }

        for (int row = i; row < i + 3; ++row) {
          bool rowResult = isRowValid(board, row);
          if (!rowResult) {
            return false;
          }
        }

        for (int col = j; col < j + 3; ++col) {
          bool colResult = isColValid(board, col);
          if (!colResult) {
            return false;
          }
        }
      }
    }
    return true;
  }
};
