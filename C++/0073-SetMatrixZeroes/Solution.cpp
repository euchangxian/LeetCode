#include <algorithm>
#include <array>
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
  void setZeroes(vector<vector<int>>& matrix) {
    int const rows = matrix.size();
    int const cols = matrix[0].size();
    vector<bool> zeroRows(rows);
    vector<bool> zeroCols(cols);

    for (int r = 0; r < rows; ++r) {
      for (int c = 0; c < cols; ++c) {
        if (matrix[r][c]) {
          continue;
        }
        zeroRows[r] = true;
        zeroCols[c] = true;
      }
    }

    for (int r = 0; r < rows; ++r) {
      if (!zeroRows[r]) {
        continue;
      }

      for (int c = 0; c < cols; ++c) {
        matrix[r][c] = 0;
      }
    }

    for (int c = 0; c < cols; ++c) {
      if (!zeroCols[c]) {
        continue;
      }
      for (int r = 0; r < rows; ++r) {
        matrix[r][c] = 0;
      }
    }
  }
};
