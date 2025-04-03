#include <array>
#include <cstring>
#include <string_view>

constexpr int DIGITS = 10;
constexpr int MAX_N = 1e4;
constexpr int MOD = 1e9 + 7;

class Solution {
 public:
  int countPalindromes(std::string_view s) {
    // Count Palindromic Subsequences of length 5.
    //
    // Exactly one character with odd frequency. The rest must be even.
    // To simplify further, set the middle element. Then, the rest must be even.
    //
    // At each character, count the prefix and suffix frequency?
    // For a character to be included in the palindromic subsequence, it must
    // have freq[c] >= 1 on the left and right side.
    // Take min(freqLeft[c], freqRight[c])
    // For each subsequent character that fulfils freqLeft|Right[c]>=1, take
    // the min, add the sum of mins so far.
    // Ah. This doesnt ensure matching.
    // i.e., does not differentiate between xycyx and xycxy
    //
    // See 4D DP.
    const int n = s.size();
    std::array<
        std::array<std::array<std::array<int, 6>, DIGITS + 1>, DIGITS + 1>,
        MAX_N + 1>
        memo;

    // WARNING: memset set bytes of memory to the specified value.
    // Only works correctly for particular values. In this case, -1 is
    // represented as 0xFFFFFFFF (all 1s).
    std::memset(memo.data(), -1, sizeof(memo));

    // sentinel digit=10
    return dfs(s, memo, 10, 10, 0, 0);
  }

 private:
  // Very similar to Buy and Sell Stock with K transactions,
  // where at each point in the subsequence, a unique decision is made.
  int dfs(std::string_view s,
          std::array<std::array<std::array<std::array<int, 6>, DIGITS + 1>,
                                DIGITS + 1>,
                     MAX_N + 1>& memo,
          int d1,
          int d2,
          int i,
          int j) {
    if (j >= 5) {
      return 1;  // valid subsequence
    }

    if (i >= s.size()) {
      return 0;
    }

    int& ans = memo[i][d1][d2][j];
    if (ans != -1) {
      return ans;
    }

    // skip
    ans = dfs(s, memo, d1, d2, i + 1, j);

    if (j == 0) {
      // choose first digit
      ans = (1LL * ans + dfs(s, memo, s[i] - '0', d2, i + 1, j + 1)) % MOD;
    }
    if (j == 1) {
      // choose second digit
      ans = (1LL * ans + dfs(s, memo, d1, s[i] - '0', i + 1, j + 1)) % MOD;
    }
    if (j == 2) {
      // choose third digit
      ans = (1LL * ans + dfs(s, memo, d1, d2, i + 1, j + 1)) % MOD;
    }
    if (j == 3 && s[i] - '0' == d2) {
      // choose fourth digit if it is equal to the second
      ans = (1LL * ans + dfs(s, memo, d1, d2, i + 1, j + 1)) % MOD;
    }
    if (j == 4 && s[i] - '0' == d1) {
      // choose fifth digit if it is equal to the first
      ans = (1LL * ans + dfs(s, memo, d1, d2, i + 1, j + 1)) % MOD;
    }

    return ans;
  }
};
