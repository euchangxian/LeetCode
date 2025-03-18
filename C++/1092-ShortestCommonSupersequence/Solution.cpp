#include <algorithm>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

class Solution {
 public:
  std::string shortestCommonSupersequence(std::string_view str1,
                                          std::string_view str2) {
    const int m = str1.size();
    const int n = str2.size();

    // dp[i][j] represents the LCS of str1[:i] and str2[:j]
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= n; ++j) {
        if (str1[i - 1] == str2[j - 1]) {
          // safe to move, since dp[j-1] will not be referenced in subsequent
          // j, for the current i.
          dp[i][j] = dp[i - 1][j - 1] + 1;
        } else {
          dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
        }
      }
    }

    // form LCS by backtracking.
    std::string lcs;
    lcs.reserve(dp[m][n]);

    // 1 indexed.
    int i = m;
    int j = n;
    while (i > 0 && j > 0) {
      if (str1[i - 1] == str2[j - 1]) {
        lcs.push_back(str1[i - 1]);
        --i;
        --j;
      } else {
        if (dp[i - 1][j] > dp[i][j - 1]) {
          lcs.push_back(str1[i - 1]);
          --i;
        } else {
          lcs.push_back(str2[j - 1]);
          --j;
        }
      }
    }

    while (i > 0) {
      lcs.push_back(str1[i - 1]);
      --i;
    }

    while (j > 0) {
      lcs.push_back(str2[j - 1]);
      --j;
    }

    std::reverse(lcs.begin(), lcs.end());
    return lcs;
  }

  std::string shortestCommonSupersequenceSpace(std::string_view str1,
                                               std::string_view str2) {
    // Super-sequence.
    // Shortest string that has both str1 and str2 as subsequences.
    // What makes it different from LCS?
    // LCS does not have to include str1 and str2 as subsequences.
    // Also, we need the actual string and not just the length.
    // Therefore, keep track of the parent, and backtrack?
    // Length is simple? find the LCS, then prepend/append the remaining
    // characters. Easier to say, lol.
    // Non-trivial to keep track of characters already in the LCS.
    // E.g.,
    // LCS           : O(mn)
    // Backtrack LCS : O(mn)
    // Append/Prepend: O(max(m,n))
    // to_string     : O(max(m,n))
    const int m = str1.size();
    const int n = str2.size();

    std::vector<std::string> dp(n + 1, "");
    for (int i = 1; i <= m; ++i) {
      std::vector<std::string> curr(n + 1, "");
      for (int j = 1; j <= n; ++j) {
        if (str1[i - 1] == str2[j - 1]) {
          // safe to move, since dp[j-1] will not be referenced in subsequent
          // j, for the current i.
          curr[j] = std::move(dp[j - 1]) + str1[i - 1];
        } else {
          int len1 = dp[j].size();
          int len2 = curr[j - 1].size();
          if (len1 > len2) {
            curr[j] = dp[j];  // not safe to move.
          } else {
            curr[j] = curr[j - 1];  // should not move.
          }
        }
      }
      dp = std::move(curr);
    }

    std::string lcs = std::move(dp[n]);
    std::string result;
    result.reserve(m + n);

    int i = 0;
    int j = 0;
    for (char c : lcs) {
      while (i < str1.size() && str1[i] != c) {
        result += str1[i++];
      }

      while (j < str2.size() && str2[j] != c) {
        result += str2[j++];
      }

      result += c;
      ++i;
      ++j;
    }

    result += str1.substr(i);
    result += str2.substr(j);
    return result;
  }
};
