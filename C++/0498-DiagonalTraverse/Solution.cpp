#include <vector>

class Solution {
 public:
  std::vector<int> findDiagonalOrder(std::vector<std::vector<int>>& mat) {
    // Given m x n matrix, return an array of all the elements in a diagonal
    // order.
    //
    // We can apply an offset of sorts where traversing in row-major order.
    // Also must note the alternating order.
    // These will allow us to map the 2D index to the 1D index?
    //
    // Nope. Note the indices of cells on the same diagonal have the same sum.
    // Using this property, we can derive the diagonal.
    // See 3446-Sort Matrix By Diagonal
    const auto m = static_cast<int>(mat.size());
    const auto n = static_cast<int>(mat[0].size());

    std::vector<std::vector<int>> diagonals(m + n - 1);
    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        diagonals[r + c].push_back(mat[r][c]);
      }
    }

    std::vector<int> result;
    result.reserve(m * n);
    bool goingUp = true;
    for (const auto& diagonal : diagonals) {
      if (!goingUp) {
        result.insert(result.end(), diagonal.begin(), diagonal.end());
      } else {
        result.insert(result.end(), diagonal.rbegin(), diagonal.rend());
      }
      goingUp = !goingUp;
    }
    return result;
  }
};
