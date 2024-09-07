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
public:
  vector<vector<int>> generateMatrix(int n) {
    vector<vector<int>> matrix(n, vector<int>(n));

    int k = 1;
    int rowStart = 0, colStart = 0, rowEnd = n - 1, colEnd = n - 1;

    while (rowStart <= rowEnd && colStart <= colEnd) {
      // top row, left to right
      for (int col = colStart; col <= colEnd; ++col) {
        matrix[rowStart][col] = k++;
      }
      ++rowStart;

      // right column, top to bottom
      for (int row = rowStart; row <= rowEnd; ++row) {
        matrix[row][colEnd] = k++;
      }
      --colEnd;

      // bottom row, right to left
      if (rowStart <= rowEnd) {
        for (int col = colEnd; col >= colStart; --col) {
          matrix[rowEnd][col] = k++;
        }
      }
      --rowEnd;

      // left col, bottom to up
      if (colStart <= colEnd) {
        for (int row = rowEnd; row >= rowStart; --row) {
          matrix[row][colStart] = k++;
        }
      }
      ++colStart;
    }
    return matrix;
  }
};
