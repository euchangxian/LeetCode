#include <algorithm>
#include <array>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

constexpr int MAX_MN = 100;
class Solution {
 public:
  int findMaxForm(std::vector<std::string>& strs, int m, int n) {
    // binary string strs, positive integers m and n
    // Return the size of the largest subset of strs such that there are at
    // most m 0s, n 1s in the subset.
    // strs.length <= 600
    // strs[i].length <= 100
    // m, n <= 100
    //
    // Hm. Seems related to bit manipulation, but unsure. First glance was
    // worded like backtracking given "subset".
    // 2D dp[i][j]
    constexpr auto countZeroOnes = [](std::string_view s) {
      std::array<int, 2> count{};
      for (char c : s) {
        ++count[c - '0'];
      }
      return count;
    };

    std::array<std::array<int, MAX_MN + 1>, MAX_MN + 1> dp{};
    for (auto [zeroCount, oneCount] :
         strs | std::views::transform(countZeroOnes)) {
      for (int zeroes = m; zeroes >= zeroCount; --zeroes) {
        for (int ones = n; ones >= oneCount; --ones) {
          dp[zeroes][ones] = std::max(
              dp[zeroes][ones], 1 + dp[zeroes - zeroCount][ones - oneCount]);
        }
      }
    }
    return dp[m][n];
  }
};
