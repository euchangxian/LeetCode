#include <algorithm>
#include <array>

constexpr int MOD = 1E9 + 7;

constexpr int MAX_POW = 5;
constexpr int MAX_N = 300;

constexpr std::array<std::array<long long, MAX_N + 1>, MAX_POW + 1> XTH_POWS =
    []() {
      std::array<std::array<long long, MAX_N + 1>, MAX_POW + 1> xthPows{};
      std::fill(xthPows[0].begin(), xthPows[0].end(), 1);
      for (int exp = 1; exp <= MAX_POW; ++exp) {
        for (int i = 1; i <= MAX_N; ++i) {
          xthPows[exp][i] = xthPows[exp - 1][i] * i;
        }
      }
      return xthPows;
    }();

class Solution {
 public:
  int numberOfWays(int n, int x) {
    // given two positive integers n and x.
    // Return the number of ways n can be expressed as the sum of the xth power
    // of unique positive integers.
    // Return mod 1E9+7.
    //
    // Prime Factorisation?
    // Not exactly.
    // Looking at the constraints:
    // 1 <= n <= 300,
    // 1 <= x <= 5
    //
    // Seems close to an exponential-time solution/backtracking
    // DP. Knapsack-like.
    // Number of ways to make a sum of K with up to ith number.
    const auto& xthPow = XTH_POWS[x];

    std::array<int, MAX_N + 1> dp{};
    dp[0] = 1;  // 1 way to make a sum of 0
    for (int i = 1; i <= n; ++i) {
      auto val = xthPow[i];
      for (int j = n; j >= val; --j) {
        if (val <= j) {
          dp[j] = (1LL * dp[j] + dp[j - val]) % MOD;
        }
      }
    }
    return dp[n];
  }
};
