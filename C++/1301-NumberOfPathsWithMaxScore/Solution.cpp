#include <string>
#include <utility>
#include <vector>

class Solution {
 public:
  std::vector<int> pathsWithMaxScore(std::vector<std::string>& board) {
    // Square board, start at bottom right square marked with 'S'.
    // Reach top left marked with 'E'.
    // The rest of the cells are numeric 1,2,...,9 or 'X' (obstacle)
    // In one move, go up, left, or up-left only if there are not obstacles
    // there.
    // Return a list of two integers: {maxSum, #pathsToGetMaxSum % 1E9+7}
    //
    // (0,0) is top-left.
    // (n-1,n-1) is bottom-right.
    constexpr int MOD = 1E9 + 7;
    constexpr int UNREACHABLE = -1;
    const auto n = static_cast<int>(board.size());

    // dp[r][c] = {max, #paths}
    // dp[r][c] = updateCountIfHigher(
    //              dp[r+1][c],
    //              dp[r][c+1],
    //              dp[r+1][c+1],
    //            )
    std::vector<std::vector<std::pair<int, int>>> dp(
        n, std::vector<std::pair<int, int>>(n, {-1, 0}));
    dp[n - 1][n - 1] = {0, 1};

    auto transition = [&](auto& curr, const auto& prev) {
      const auto& [prevMax, prevCount] = prev;
      if (prevMax == UNREACHABLE) {
        return;
      }

      auto& [currMax, currCount] = curr;
      if (currMax < prevMax) {
        curr = prev;
      } else if (currMax == prevMax) {
        currCount = (static_cast<long long>(currCount) + prevCount) % MOD;
      }
    };

    for (auto r = n - 1; r >= 0; --r) {
      for (auto c = n - 1; c >= 0; --c) {
        if (r == n - 1 && c == n - 1) {
          continue;
        }

        if (board[r][c] == 'X') {
          continue;
        }

        if (r + 1 < n) {
          transition(dp[r][c], dp[r + 1][c]);
        }
        if (c + 1 < n) {
          transition(dp[r][c], dp[r][c + 1]);
        }
        if (r + 1 < n && c + 1 < n) {
          transition(dp[r][c], dp[r + 1][c + 1]);
        }

        if (auto& maxSum = dp[r][c].first; maxSum != UNREACHABLE) {
          maxSum += board[r][c] == 'E' ? 0 : board[r][c] - '0';
        }
      }
    }

    return dp[0][0].first == UNREACHABLE
               ? std::vector{0, 0}
               : std::vector{dp[0][0].first, dp[0][0].second};
  }
};
