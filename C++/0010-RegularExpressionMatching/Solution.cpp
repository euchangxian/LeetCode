#include <string>
#include <vector>

class Solution {
  bool match(char c, char p) { return c == p || p == '.'; }

 public:
  bool isMatch(std::string s, std::string p) {
    // '.' matches any single character
    // '*' matches zero or more of the preceding element.
    // Return true if the pattern p matches the given string s
    // Guaranteed that '*' will occur after a previous valid character.
    //
    // Naively, match s[i] == p[i] || s[i] == '.'.
    // If p[i] == '*'? Greedily match characters?
    // Counter-example: s = "aaaab", p = ".*b" - If greedily-matched, then
    // s will be completely covered by the pattern ".*", leaving b unmmatched.
    // But it seems that normal english alphabets can be greedily matched.
    //
    // Then, does this mean that the pattern ".*" spawns a recursive call of
    // isMatch(s[i:], removePrefix(p, ".*")) for all subsequent i?

    int m = s.length();
    int n = p.length();
    // dp[i][j] represents if s[:i] matches p[:j] (note exclusive end)
    // Trivially, if s[i-1] == p[j-1] || p[j - 1] == '.'
    // then dp[i][j] = dp[i-1][j-1] && true; (dp[i-1][j-1] simplified)
    //
    // If p[j-1] = '*', let the preceding char, p[j-2] be pre.
    // Then there are two possible outcomes:
    //  1. if s[i-1] != pre, then dp[i][j] = dp[i][j-2].
    //    i.e., if the current char at s is not equal to the preceding char,
    //    then it is equivalent to taking 0 repeats of the preceding char,
    //    dp[i][j-2].
    //  2. if pre == s[i-1] or '.', then
    //     dp[i][j] = dp[i - 1][j] (take multiple times)
    //             && (s[i-1] == p[j-1] || p[j-1] == '.') (char must match)
    std::vector<std::vector<bool>> dp(m + 1, std::vector<bool>(n + 1, false));
    dp[0][0] = true;  // vacuously true
    for (int j = 1; j <= n; ++j) {
      if (p[j - 1] == '*') {
        dp[0][j] = dp[0][j - 2];  // vacuously true for kleene star
      }
    }

    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= n; ++j) {
        if (match(s[i - 1], p[j - 1])) {
          dp[i][j] = dp[i - 1][j - 1];  // && true
          continue;
        }

        // not same char, and not '.' pattern
        if (p[j - 1] != '*') {
          // not necessary, since initalized to false. For clarity
          dp[i][j] = false;
          continue;
        }

        // if '*'
        char preceding = p[j - 2];  // no need out-of-bounds check
        dp[i][j] = dp[i][j - 2];    // repeat preceding character 0 times

        if (match(s[i - 1], preceding)) {
          // while s[i-1] matches the preceding pattern character,
          // try matching the pattern.
          dp[i][j] = dp[i][j] || dp[i - 1][j];
        }
      }
    }

    return dp[m][n];
  }
};
