#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class Solution {
private:
  bool isMagicSquare(vector<vector<int>> const &grid, int rStart, int cStart) {
    vector<bool> seen(10); // Distinct from 1 to 9

    vector<int> rowSum(3);
    vector<int> colSum(3);
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        int num = grid[rStart + i][cStart + j];
        if (num < 1 || num > 9 || seen[num]) {
          return false;
        }

        seen[num] = true;
        rowSum[i] += num;
        colSum[j] += num;
      }
    }

    for (int i = 0; i < 3; ++i) {
      if (rowSum[i] != 15 || colSum[i] != 15) {
        return false;
      }
    }

    // Check diagonal
    int rightDiagonal = grid[rStart][cStart] + grid[rStart + 1][cStart + 1] +
                        grid[rStart + 2][cStart + 2];
    int leftDiagonal = grid[rStart + 2][cStart] + grid[rStart + 1][cStart + 1] +
                       grid[rStart][cStart + 2];

    return rightDiagonal == 15 && leftDiagonal == 15;
  }

public:
  int numMagicSquaresInside(vector<vector<int>> &grid) {
    int rows = grid.size();
    int cols = grid[0].size();

    if (rows < 3 || cols < 3) {
      return 0;
    }

    // Seems that as long as the numbers in the 3x3 grid are distinct
    // and the rows, columns and diagonals add to 15, its a magical square
    // Try brute-force sliding window
    int result = 0;
    for (int r = 0; r < rows - 3 + 1; ++r) {
      for (int c = 0; c < cols - 3 + 1; ++c) {
        result += isMagicSquare(grid, r, c);
      }
    }
    return result;
  }
};
