#include <array>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  int countServers(std::vector<std::vector<int>>& grid) {
    // m * n binary matrix.
    // grid[i][j] == 1 => server, 0 => no server.
    // two servers are communicating if they are on the same row/column.
    // Number of servers that communicate with ANY other server.
    // UF needs to be augmented to count the size of the component. Non-trivial
    // to union an entire row/column too. A Sentinel could be used, but there
    // should be a simpler way.
    // rowCount/colCount? Not exactly. Previously added servers are hard to
    // keep track of. I.e., double-counting, under-counting.
    // Nope. Do two pass. Second pass will check for each server, if it's
    // row/column count is more than 1.
    const int m = grid.size();
    const int n = grid[0].size();

    std::array<int, 250> rowCount{};
    std::array<int, 250> colCount{};
    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        if (grid[r][c]) {
          ++rowCount[r];
          ++colCount[c];
        }
      }
    }

    int result = 0;
    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        if (grid[r][c] && (rowCount[r] > 1 || colCount[c] > 1)) {
          ++result;
        }
      }
    }
    return result;
  }
};
