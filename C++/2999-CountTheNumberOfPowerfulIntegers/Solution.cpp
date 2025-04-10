#include <algorithm>
#include <array>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

using i64 = long long;

constexpr int MAX_DIGITS = 15;
constexpr std::array<i64, MAX_DIGITS> MULT = []() {
  std::array<i64, MAX_DIGITS> mult{};
  i64 m = 1LL;
  for (int i = mult.size() - 1; i >= 0; --i) {
    mult[i] = m;
    m *= 10;
  }
  return mult;
}();

class Solution {
 public:
  i64 numberOfPowerfulInt(i64 start,
                          i64 finish,
                          int limit,
                          std::string_view s) {
    // NOTE: Tapped out. Digit DP. Cool stuff.
    // Essentially, dp[i][isTight], where isTight indicates that the prefix
    // digits up to index i-1 (inclusive) are equal to s[:i-1]. Thus, the
    // next digit must respect that bound, i.e., d <= s[i]
    auto prefixPowerful = [this, limit, s](i64 upperBound) -> i64 {
      std::string ub = std::to_string(upperBound);
      if (ub.size() < s.size()) {
        return 0;
      }

      // positions that can be set.
      const int n = ub.size() - s.size();

      // check the last K digits, K=suff.size.
      // If ub[i] >= suff[i] for all K, then return true.
      // This is crucial for the base case. In the case where tight is true,
      // then if the suffix is not possible, return 0.
      // A Lexicographical check is sufficient.
      bool isSuffixPossible =
          s <= std::string_view{ub}.substr(ub.size() - s.size());

      std::array<std::array<i64, 2>, MAX_DIGITS + 1> dp{};

      // Same base case as top-down
      dp[n][0] = 1;
      dp[n][1] = isSuffixPossible ? 1 : 0;

      for (int i = n - 1; i >= 0; --i) {
        // NOTE: Unlike top-down, we "unroll" the for d in [0..loopBound] loop.
        // A little harder to understand, but wow.

        // Not tight case: Take all digits [0..limit]
        dp[i][0] = (limit + 1) * dp[i + 1][0];

        // same variable name for clarity, though technically not a loop.
        int loopBound = std::min(ub[i] - '0', limit);
        if (loopBound == ub[i] - '0') {
          // `nextTight` == true case.
          // Essentially, [0..loopBound-1] * dp[i+1][0]  +  dp[i+1][1]
          // Insane unrolling.
          dp[i][1] = (loopBound * dp[i + 1][0]) + dp[i + 1][1];
        } else {
          dp[i][1] = ((limit + 1) * dp[i + 1][0]);
        }
      }

      return dp[0][1];
    };

    return prefixPowerful(finish) - prefixPowerful(start - 1);
  }

  i64 numberOfPowerfulMemo(i64 start,
                           i64 finish,
                           int limit,
                           std::string_view s) {
    // NOTE: Tapped out. Digit DP. Cool stuff.
    // Essentially, dp[i][isTight], where isTight indicates that the prefix
    // digits up to index i-1 (inclusive) are equal to s[:i-1]. Thus, the
    // next digit must respect that bound, i.e., d <= s[i]
    auto prefixPowerful = [this, limit, s](i64 upperBound) -> i64 {
      std::string ub = std::to_string(upperBound);
      if (ub.size() < s.size()) {
        return 0;
      }

      // positions that can be set.
      const int n = ub.size() - s.size();

      // check the last K digits, K=suff.size.
      // If ub[i] >= suff[i] for all K, then return true.
      // This is crucial for the base case. In the case where tight is true,
      // then if the suffix is not possible, return 0.
      // A Lexicographical check is sufficient.
      bool isSuffixPossible =
          s <= std::string_view{ub}.substr(ub.size() - s.size());

      // memo[idx][tight]
      std::vector<std::array<i64, 2>> memo(n, {-1LL, -1LL});
      return dfs(limit, ub, isSuffixPossible, memo, 0, true);
    };

    return prefixPowerful(finish) - prefixPowerful(start - 1);
  }

 private:
  i64 dfs(int limit,
          std::string_view ub,
          bool isSuffixPossible,
          std::vector<std::array<i64, 2>>& memo,
          int idx,
          bool tight) {
    if (idx >= memo.size()) {
      if (tight) {
        return isSuffixPossible ? 1 : 0;
      }
      return 1;
    }

    i64& ans = memo[idx][tight];
    if (ans != -1LL) {
      return ans;
    }

    ans = 0;
    i64 loopBound = tight ? std::min(ub[idx] - '0', limit) : limit;
    for (int d = 0; d <= loopBound; ++d) {
      bool nextTight = tight && (d == ub[idx] - '0');

      ans += dfs(limit, ub, isSuffixPossible, memo, idx + 1, nextTight);
    }
    return ans;
  }

  i64 numberOfPowerfulIntTLE(i64 start,
                             i64 finish,
                             int limit,
                             std::string_view s) {
    // s represents a positive integer.
    // A positive integer x is called powerful if it ends with s (s is a
    // suffix), and each digit in x is at most limit.
    // Return the total number of powerful integers in the range [start..finish]
    //
    // Note the constraints start <= finish <= 10^15. A solution based off these
    // will not work.
    // Though, it seems more intuitive for a solution based on s.
    // s is at most 10^16.
    // Given that s must be a suffix, we can prepend digits <= limit to s
    // iteratively.
    // d + s == d * 10^(s.length+1) + s
    //
    // Not too sure if this is DP, or just iterative counting.
    // Think DP is necessary.
    // Consider the case limit=9,finish=1234, s=4
    // Suppose we prepend [1..9] in the first step, [1..9] in the second step,
    // making for 100 combinations. Then, at the last step, we must consider
    // the previous numbers when attempting to prepend a digit. E.g., we can
    // only prepend 1 to 111, ..., 234. Prepending 1 to 334 will exceed.
    //
    // Hm. What if we look at it from another perspective? Start with empty
    // slots like: num = _ _ _ s, where the number of slots is the number of
    // digits in finish - s.size.
    // Thus, starting from i=0, the first slot, we can fill in [0..limit],
    // and so on.
    // But how to determine if the number created is within [start..finish],
    // without saving the entire string as state?
    // Technically, with the constraints, the number can be represented with
    // a long long, with precomputed exponents?
    // dfs(i, num)
    //
    // ... Should have done a runtime analysis first.
    // Given that we have at most 15 digits, with 10 choices available at each
    // position, our runtime is 10^15
    // Furthermore, there is no overlapping subproblems with this formulation.
    const int N = MAX_DIGITS - s.size();
    std::vector<std::unordered_map<i64, i64>> memo(MAX_DIGITS);
    i64 base = stoll(s);
    return dfsTLE(N, start, finish, limit, memo, 0, base);
  }

  // std::stoll does not accept string_view.
  i64 stoll(std::string_view s) {
    i64 result = 0LL;
    for (char c : s) {
      result = result * 10LL + (c - '0');
    }
    return result;
  }

  i64 dfsTLE(int N,
             i64 start,
             i64 finish,
             int limit,
             std::vector<std::unordered_map<i64, i64>>& memo,
             int idx,
             i64 base) {
    if (idx >= N) {
      return base >= start && base <= finish;
    }

    auto it = memo[idx].find(base);
    if (it != memo[idx].end()) {
      return it->second;
    }

    i64& ans = memo[idx][base];  // default-initialized

    // set '0' in current position.
    ans += dfsTLE(N, start, finish, limit, memo, idx + 1, base);
    for (int d = 1; d <= limit; ++d) {
      i64 num = d * MULT[idx] + base;
      if (num > finish) {
        break;
      }
      // current num is Powerful.
      ans += dfsTLE(N, start, finish, limit, memo, idx + 1, num);
    }
    return ans;
  }
};
