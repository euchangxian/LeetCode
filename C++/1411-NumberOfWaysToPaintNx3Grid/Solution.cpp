#include <array>
#include <cstring>

enum Color {
  R = 0b01,
  G = 0b10,
  B = 0b11,
};
constexpr std::array<Color, 3> COLORS{{Color::R, Color::G, Color::B}};
constexpr int MOD = 1E9 + 7;
constexpr int MAX_N = 5000;
constexpr int MAX_S = 4 * 4 * 4;  // 4^3
constexpr int COLS = 3;

class Solution {
 public:
  int numOfWays(int n) {
    // Paint an Nx3 grid with one of 3 colors.
    // Iterate row by row
    std::array<std::array<int, MAX_S>, MAX_N> memo;
    std::memset(memo.data(), -1, sizeof(memo));

    auto getColorAtCol = [&](int mask, int col) -> Color {
      return static_cast<Color>(mask >> (2 * col) & 0b11);
    };

    auto setColorAtCol = [&](int mask, int col, Color c) -> int {
      return mask | (static_cast<int>(c) << (2 * col));
    };

    auto dfs = [&](this auto&& dfs, int prevMask, int row, int currMask,
                   int col) -> int {
      if (row == n) {
        return 1;  // valid coloring
      }

      if (col == COLS) {
        return dfs(currMask, row + 1, 0, 0);
      }

      if (col == 0 && memo[row][prevMask] != -1) {
        return memo[row][prevMask];
      }

      long long ans = 0;
      for (Color c : COLORS) {
        if (getColorAtCol(prevMask, col) != c &&
            (col == 0 || getColorAtCol(currMask, col - 1) != c)) {
          ans = (ans +
                 dfs(prevMask, row, setColorAtCol(currMask, col, c), col + 1)) %
                MOD;
        }
      }

      if (col == 0) {
        memo[row][prevMask] = ans;
      }
      return ans;
    };
    return dfs(0, 0, 0, 0);
  }
};
