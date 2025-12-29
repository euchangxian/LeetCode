#include <array>
#include <bitset>
#include <ranges>
#include <string>
#include <string_view>
#include <tuple>
#include <vector>

constexpr int LETTERS = 6;
constexpr int MAX_SEEN = 8 * 8 * 8 * 8 * 8 * 8;  // 8^6
class Solution {
 public:
  bool pyramidTransition(std::string_view bottom,
                         std::vector<std::string>& allowed) {
    // Blocks form a pyramid. Each block is represented by a letter.
    // Allow only specific triangular patterns, where a triangular pattern
    // is a single block stacked on two blocks.
    // Given as a 3-letter string where the first 2 characters represent the
    // left and right bottom blocks, the last character represent the top.
    // Start with a bottom row.
    // Return true if the pyramid can be built such that every triangular
    // pattern is in allowed.
    // False otherwise.
    //
    // Constraints are small => backtracking?
    // 2 <= bottom.length <= 6
    // 0 <= allowed.length <= 216 => 6^3. (set of all permutations)
    // Letters = {A, B, C, D, E, F} (only 6 characters.)
    //
    // A built-pyramid means a single block at the top.
    // Therefore, the number of layers is determined by bottom.length,
    // height = bottom.length
    //
    // Can parse into a (left -> right -> top) lookup-table.
    // Then recurse.
    const auto n = static_cast<int>(bottom.size());
    std::array<std::array<int, LETTERS>, LETTERS> triangle{};

    for (const auto& [left, right, top] :
         allowed | std::views::transform([](std::string_view s) {
           return std::make_tuple(s[0] - 'A', s[1] - 'A', s[2] - 'A');
         })) {
      triangle[left][right] |= (1 << top);
    }

    std::vector<std::vector<int>> pyramid(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
      pyramid[n - 1][i] = bottom[i] - 'A';
    }

    std::bitset<MAX_SEEN> seen{};
    auto dfs = [&](this auto&& dfs, int repr, int row, int i) {
      if (row == 1 && i == 1) {
        return true;
      }
      if (i >= row) {
        if (seen[repr]) {
          return false;
        }

        seen[repr] = true;
        return dfs(0, row - 1, 0);
      }

      auto left = pyramid[row][i];
      auto right = pyramid[row][i + 1];
      auto possible = triangle[left][right];
      for (int top = 0; top < LETTERS; ++top) {
        if (possible & (1 << top)) {
          pyramid[row - 1][i] = top;

          // Each block can have 6 possible encodings {A, B, C, ...}.
          // Hence we need to use 3 bits (2^3 possible states) for each block.
          if (dfs((repr << 3) + (top + 1), row, i + 1)) {
            return true;
          }
        }
      }
      return false;
    };

    return dfs(0, n - 1, 0);
  }
};
