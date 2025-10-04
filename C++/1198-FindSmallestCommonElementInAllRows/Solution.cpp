#include <array>
#include <vector>

constexpr int MAX_VAL = 1E4;

class Solution {
 public:
  int smallestCommonElement(std::vector<std::vector<int>>& mat) {
    // Given m x n matrix mat, where every row is sorted in increasing order,
    // return the smallest common element in all rows, or -1.
    //
    // Its like AND-ing every row together.
    // Ah. Strictly increasing => no duplicates in each row.
    // Count frequency of elements. If freq[e] = #rows, then it must be the
    // common element.
    const auto rows = static_cast<int>(mat.size());
    std::array<int, MAX_VAL + 1> freq{};
    for (const auto& row : mat) {
      for (auto x : row) {
        ++freq[x];
      }
    }

    for (int x = 1; x <= MAX_VAL; ++x) {
      if (freq[x] == rows) {
        return x;
      }
    }

    return -1;
  }
};
