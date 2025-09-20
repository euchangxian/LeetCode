#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution {
 public:
  int numSubmat(std::vector<std::vector<int>>& mat) {
    // Given an m x n binary matrix, return the number of submatrices that
    // have all ones.
    // 1 <= m,n <= 150
    //
    // Effectively count rectangles with all '1's, unlike other simpler variants
    // that need only count squares.
    // Tough.
    const std::size_t m = mat.size();
    const std::size_t n = mat[0].size();
  }
};
