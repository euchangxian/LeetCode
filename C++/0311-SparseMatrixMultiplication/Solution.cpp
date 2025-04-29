#include <vector>

class Solution {
 public:
  std::vector<std::vector<int>> multiply(std::vector<std::vector<int>>& mat1,
                                         std::vector<std::vector<int>>& mat2) {
    const int m = mat1.size();
    const int k = mat1[0].size();
    const int n = mat2[0].size();

    std::vector result(m, std::vector<int>(n, 0));
    for (int r = 0; r < m; ++r) {
      for (int i = 0; i < k; ++i) {
        if (mat1[r][i] == 0) {
          continue;
        }
        for (int c = 0; c < n; ++c) {
          if (mat2[i][c] == 0) {
            continue;
          }
          result[r][c] += mat1[r][i] * mat2[i][c];
        }
      }
    }
    return result;
  }
};
