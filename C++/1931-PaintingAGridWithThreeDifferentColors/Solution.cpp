#include <algorithm>
#include <array>

constexpr int MOD = 1E9 + 7;
constexpr int MAX_M = 5;
constexpr int MAX_N = 1000;
constexpr int MAX_STATES = 4 * 4 * 4 * 4 * 4;  // 4 ^ 5

// Could name them RED|GREEN|BLUE I guess.
// 2 bits per color.
enum Color {
  R = 0b01,
  G = 0b10,
  B = 0b11,
};

class Solution {
 public:
  int colorTheGrid(int m, int n) {
    // paint an m x n grid Red Green or Blue, such that no two adjacent cells
    // have the same color.
    // Return the number of ways to color the grid mod 1E9+7
    //
    // Wew. Can we solve the 1D variant, and see if we can generalize it?
    // Note that we do not have a requirement to keep the number of R|G|B cells
    // equal.
    // Thus, suppose we have a 1xN row.
    // 3 * 2 * ... * 2, i.e., 3 * 2^(N-1) ways
    // where there are 3 ways to choose the first cell's color, then 2 ways
    // to choose the subsequent cell's colors to avoid picking the same color
    // as the previous.
    //
    // How do we generalize this to multiple rows...?
    // Note the constraints: 1 <= m <= 5, 1 <= n <= 1000
    // Thus, we can possible solve for each column.
    // Given that each column's coloring depends on the current column (i.e.,
    // adjacent cells above and below), and the previous column only,
    // can we derive a recurrence?
    // We need the number of ways to color this cell R|G|B, given the state
    // of the cells above/below, and the cell to the left.
    // i.e., naively,
    // dp[r][c][color]=dp[r-1][c][~color]*dp[r+1][c][~color]*dp[r][c-1][~color]
    // Though, ~color needs to be expressed using bitmask operations.
    // Thus, given the constraints, we have 5 * 1000 * 2^3 = ~40 000
    // subproblems, each of which take O(1) time to solve.
    // Hm... The representation needs to be tweaked a little, to dp[c][r][color]
    // since we want to iterate column by column, then solve for each row.
    // Hmmmm... Not really. Notice we cant get the solution to r-1, r+1. Its
    // a cyclic dependency, not a DAG. Wrong DP state.
    //
    // Hm. We can color a single column 3 * 2^(m-1) ways, which we derived
    // earlier.
    // How do we represent the column as a singular state, where we just need
    // the previous column to be different, i.e., each row is different?
    // Hm. Maybe some complex mapping to the state.
    // Hm. Bitmasks still? We have at most m<=5, so we can allocate 3 bits for
    // each row, making it 3*5=15 bits used at most.
    // Then, each partition can have only 1 set bit.
    // NOTE: tapped out.
    // We can use two bits to represent the colors. Then do precomputation to
    // map the state, along with their adjacent states (that have different
    // colors per row).
    // Then, the transition becomes simpler: dp[c][S] = sum(dp[c-1][S']) where
    // S` has a different color in every row from S.
    // The issue becomes how to compute S and its neighbours.

    auto getColor = [&](int mask, int row) -> Color {
      return static_cast<Color>((mask >> (2 * row)) & 0b11);
    };
    auto setColor = [&](int mask, int row, Color color) -> int {
      return mask | (static_cast<int>(color) << (2 * row));
    };

    std::array<std::array<int, MAX_STATES>, MAX_N> memo;
    std::memset(memo.data(), -1, sizeof(memo));
    auto dfs = [&](this auto&& dfs, int col, int prevMask, int row,
                   int currMask) -> int {
      if (col == n) {
        return 1;  // valid
      }

      if (row == 0 && memo[col][prevMask] != -1) {
        return memo[col][prevMask];  // don't re-compute
      }
      if (row == m) {
        return dfs(col + 1, currMask, 0, 0);
      }

      // Try setting the colors in each row.
      // long long to implicitly promote, avoiding overflow.
      long long ans = 0;
      for (Color c : {Color::R, Color::G, Color::B}) {
        if (getColor(prevMask, row) != c &&
            (row == 0 || getColor(currMask, row - 1) != c)) {
          ans =
              (ans + dfs(col, prevMask, row + 1, setColor(currMask, row, c))) %
              MOD;
        }
      }
      if (row == 0) {
        memo[col][prevMask] = ans;
      }
      return ans;
    };

    return dfs(0, 0, 0, 0);
  }
};
