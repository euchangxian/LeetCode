#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class Solution {
 public:
  int maxEqualRowsAfterFlips(std::vector<std::vector<int>>& matrix) {
    // m * n binary matrix
    // 1 <= m, n <= 300 -> Try flipping every column, count equal rows.
    // JK thats backtracking.
    // Notice that if we represent each row in the matrix as an integer in
    // binary representation, the problem is simpler now.
    // Each operation is doing an XOR between rows.
    // i.e., if row1 = 00011
    //          row2 = 11100
    // Then after flipping either the first 3 columns, or the last 2 columns,
    // we will get the best outcome.
    // i.e., want to find the max number of rows such that
    // - row_i XOR row_j = 0, or
    // - row_i == row_j.
    //
    // HashMap!! The first condition can be checked by negating the current row.
    // What to store as Key tho? Can't directly convert to integer
    // representation. String? L...
    const std::size_t rows = matrix.size();
    const std::size_t cols = matrix[0].size();

    std::unordered_map<std::string, int> patterns;
    for (auto& row : matrix) {
      std::string pattern(cols, '0');

      // Interesting optimization here.
      // Canonical Forms are used, since we are representing the rows as a
      // String, which cannot be XOR-ed or negated easily.
      // Therefore, we check the first bit. WLOG, if the bit is '1', then
      // we flip the rest of the bit. This is essentially equivalent to
      // negating the number represented by the row, which will help us count
      // the number of rows matching the condition as stated above.
      bool shouldFlip = row[0];
      for (int c = 0; c < cols; ++c) {
        pattern[c] = '0' + (row[c] ^ shouldFlip);  // XOR
      }

      ++patterns[pattern];
    }

    const auto& maxPattern = std::max_element(
        patterns.begin(), patterns.end(), [](const auto& kv1, const auto& kv2) {
          return kv1.second < kv2.second;
        });

    return maxPattern->second;
  }
};
