#include <algorithm>
#include <array>
#include <string_view>
#include <utility>
#include <vector>

constexpr int MOD = 1E9 + 7;
class Solution {
 public:
  int numberOfWays(std::string_view corridor) {
    const auto n = static_cast<int>(corridor.size());

    int zero = 0;
    int one = 0;
    int two = 1;

    for (auto c : corridor) {
      if (c == 'S') {
        zero = one;
        std::swap(one, two);
      } else {
        two = (two + zero) % MOD;
      }
    }
    return zero;
  }

  int numberOfWaysDP(std::string_view corridor) {
    const auto n = static_cast<int>(corridor.size());
    std::vector<std::array<int, 3>> dp(n + 1);
    dp[n][0] = 0;
    dp[n][1] = 0;
    dp[n][2] = 1;

    for (int i = n - 1; i >= 0; --i) {
      if (corridor[i] == 'S') {
        dp[i][0] = dp[i + 1][1];
        dp[i][1] = dp[i + 1][2];

        dp[i][2] = dp[i + 1][1];
      } else {
        dp[i][0] = dp[i + 1][0];
        dp[i][1] = dp[i + 1][1];

        dp[i][2] = (dp[i + 1][0] + dp[i + 1][2]) % MOD;
      }
    }
    return dp[0][0];
  }

  int numberOfWaysMemo(std::string_view corridor) {
    // corridor of length n
    // corridor[i] = 'S'|'P',
    // S: Seat
    // P: Plant
    // Dividers can be installed at each position between i-1 | i, 1<=i<=n-1
    // Divide the corridor into partitions where each section has exactly
    // two Seats and any number of Plants.
    // Return the number of ways to divide the corridor, modulo 1E9+7.
    //
    // Expand a prefix until it has two Seats, every subsequent Plant/Seat
    // becomes a possible divider.
    const auto n = static_cast<int>(corridor.size());

    std::vector<std::array<int, 3>> memo(n, {-1, -1, -1});
    auto dfs = [&](this auto&& dfs, int idx, int seats) {
      if (idx >= n) {
        return seats == 2 ? 1 : 0;
      }

      auto& result = memo[idx][seats];
      if (result != -1) {
        return result;
      }

      if (seats == 2) {
        if (corridor[idx] == 'S') {
          // Close this section, start a new section with 1 seat.
          result = dfs(idx + 1, 1);
        } else {
          // Otherwise, two choices:
          // - Close current section, start a new section with 0 seats.
          // - Continue growing this section.
          result = (dfs(idx + 1, 0) + dfs(idx + 1, 2)) % MOD;
        }
      } else {
        result = dfs(idx + 1, seats + (corridor[idx] == 'S'));
      }

      return result;
    };

    return dfs(0, 0);
  }
};
