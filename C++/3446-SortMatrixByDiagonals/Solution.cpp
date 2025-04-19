#include <algorithm>
#include <functional>
#include <vector>

class Solution {
 public:
  std::vector<std::vector<int>> sortMatrix(
      std::vector<std::vector<int>>& grid) {
    // Given an NxN square matrix.
    // Sort matrix in the bottom-left (including the middle) triangle by
    // non-increasing order (std::greater<>),
    // sort matrix in the upper-right triangle by non-decreasing order
    //
    // Given that we can assign an ID to a diagonal by doing i-j, we can
    // determine if a diagonal is in the bottom-left if i-j >= 0,
    // and in the upper-right if i-j < 0
    const int N = grid.size();

    auto idx = [N](int r, int c) -> int { return r - c + N - 1; };
    auto bottomLeft = [N](int idx) -> bool { return idx - (N - 1) >= 0; };

    std::vector<std::vector<int>> diagonals(N + N - 1);
    for (int r = 0; r < N; ++r) {
      for (int c = 0; c < N; ++c) {
        diagonals[idx(r, c)].push_back(grid[r][c]);
      }
    }

    for (int idx = 0; idx < diagonals.size(); ++idx) {
      if (bottomLeft(idx)) {
        // since we are iterating in normal order, we want to pop the largest
        // value from the back, so we can sort the bottom-left diaognal by
        // non-increasing order.
        std::sort(diagonals[idx].begin(), diagonals[idx].end(), std::less<>{});
      } else {
        std::sort(diagonals[idx].begin(), diagonals[idx].end(),
                  std::greater<>{});
      }
    }

    for (int r = 0; r < N; ++r) {
      for (int c = 0; c < N; ++c) {
        int dIdx = idx(r, c);
        int val = diagonals[dIdx].back();
        diagonals[dIdx].pop_back();
        grid[r][c] = val;
      }
    }
    return grid;
  }
};
