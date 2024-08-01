#include <climits>
#include <vector>

using namespace std;
class Solution {
public:
  vector<int> luckyNumbers(vector<vector<int>> const &matrix) {
    int n = matrix.size();
    int m = matrix[0].size();

    // the i-th index contains the column index of the min element in the i-th
    // row
    vector<int> minOfRow(n, 0);

    // the i-th index contains the maximum element of the i-th column
    vector<int> maxOfCol(m, INT_MIN);
    for (int row = 0; row < n; ++row) {
      for (int col = 0; col < m; ++col) {
        if (matrix[row][col] < matrix[row][minOfRow[row]]) {
          minOfRow[row] = col;
        }

        maxOfCol[col] = max(maxOfCol[col], matrix[row][col]);
      }
    }

    vector<int> result;
    result.reserve(n);
    for (int i = 0; i < n; ++i) {
      if (matrix[i][minOfRow[i]] == maxOfCol[minOfRow[i]]) {
        result.push_back(matrix[i][minOfRow[i]]);
      }
    }
    return result;
  }
};
