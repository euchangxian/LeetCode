#include <algorithm>
#include <vector>

class Solution {
 public:
  std::vector<std::vector<int>> restoreMatrix(std::vector<int>& rowSum,
                                              std::vector<int>& colSum) {
    int n = rowSum.size();
    int m = colSum.size();

    std::vector<std::vector<int>> matrix(n, std::vector<int>(m, 0));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        // Greedily take the most
        int current = std::min(rowSum[i], colSum[j]);

        // update the remaining sum
        rowSum[i] -= current;
        colSum[j] -= current;

        matrix[i][j] = current;
      }
    }

    return matrix;
  }
};
