#include <vector>

class Solution {
 public:
  bool areSimilar(std::vector<std::vector<int>>& mat, int k) {
    // m*n integer matrix, integer k.
    // The following happens k times:
    // - Even indexed rows are shifted left cyclically.
    // - Odd indexed rows are shifted right cyclically.
    // Return true if the final modified matrix is identical to the original.
    //
    // Simulation is probably the cleanest.
    const auto m = static_cast<int>(mat.size());
    const auto n = static_cast<int>(mat[0].size());

    k %= n;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (mat[i][j] != mat[i][(j + k) % n]) {
          return false;
        }
      }
    }
    return true;
  }
};
