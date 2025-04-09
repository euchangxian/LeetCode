#include <array>
#include <string_view>
#include <vector>

constexpr int MOD = 1e9 + 7;
constexpr int MAX_N = 1e5;

class Solution {
 public:
  int numberOfArrays(std::string_view s, int k) {
    // Same transitions as top-down.
    const int n = s.size();
    std::array<int, MAX_N + 1> dp{};
    dp[n] = 1;

    // Fill up the table from the back first.
    for (int idx = n - 1; idx >= 0; --idx) {
      if (s[idx] == '0') {
        continue;
      }

      long long num = 0LL;
      for (int i = idx; i < n; ++i) {
        num = num * 10 + s[i] - '0';
        if (num > k) {
          // NOTE: < 1 check is not necessary, since we skip leading zeros.
          break;
        }

        dp[idx] = (dp[idx] + dp[i + 1]) % MOD;
      }
    }
    return dp[0];
  }

  int numberOfArraysMemo(std::string_view s, int k) {
    // Count the number of ways to partition s such that no subarrays start
    // with '0'. (Or, number of possible integers)
    //
    // Choices:
    // - add to previous number. (if 1 <= x <= k)
    // - start a new number (if not '0')
    //
    // Base Cases:
    // - i >= s.size; return 1; // valid-so-far
    //
    // dfs(i) {
    //   int num = 0
    //   for j in [i..n]:
    //     num = num * 10 + d
    //     dfs(i+1) // if num >= 1 && num <= k
    // }
    const int n = s.size();
    std::vector<int> memo(n, -1);
    return dfs(s, k, memo, 0);
  }

 private:
  int dfs(std::string_view s, int k, std::vector<int>& memo, int idx) {
    if (idx >= s.size()) {
      return 1;
    }

    int& ans = memo[idx];
    if (ans != -1) {
      return ans;
    }

    ans = 0;
    long long num = 0LL;
    for (int i = idx; i < s.size(); ++i) {
      num = num * 10 + s[i] - '0';
      if (num < 1 || num > k) {
        break;
      }

      ans = (1LL * ans + dfs(s, k, memo, i + 1)) % MOD;
    }
    return ans;
  }
};
