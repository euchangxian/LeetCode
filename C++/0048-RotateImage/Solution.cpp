#include <algorithm>
#include <vector>

class Solution {
 public:
  void rotate(std::vector<std::vector<int>>& matrix) {
    // Clockwise rotation by 90-degrees can be represented by the matrix R:
    // R = [[ 0, 1],
    //      [-1, 0]]
    //
    // For any point (x, y), the rotation is given by:
    // [x']   [[ 0, 1]   [x]   [ y]
    // [y'] = [-1, 0]] * [y] = [-x]
    //
    // This rotation can be decomposed into two steps:
    // 1. Reflection about x-axis
    //
    // Reflection Matrix F = [[ 1,  0],
    //                        [ 0, -1]]
    //
    // 2. Transposition
    //
    // Transpose Matrix T = [[0, 1],
    //                       [1, 0]]
    //
    // The composition of these transformations gives us the rotation:
    // R = T * F = [[0, 1],   [[ 1,  0],   [[ 0, 1],
    //              [1, 0]] *  [ 0, -1]] = [-1, 0]]
    int n = matrix.size();

    // Reflect against x-axis: f(x, y) = (x, -y)
    std::reverse(matrix.begin(), matrix.end());

    // Transpose: g(x, -y) = (-y, x)
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        std::swap(matrix[i][j], matrix[j][i]);
      }
    }
  }
};
