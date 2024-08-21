#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class Solution {
private:
  string removeConsecutive(string const &s) {
    string result;
    int i = 0;
    while (i < s.length()) {
      char c = s[i++];
      result += c;

      // Skip consecutive occurences
      while (i < s.length() && s[i] == c) {
        ++i;
      }
    }
    return result;
  }

public:
  int strangePrinter(string s) {
    // if all contiguous, then only one turn is required to print out that
    // sequence.
    s = removeConsecutive(s);
    int n = s.length();

    // dp[i][j] represents the number of turns required to print the
    // substring s[i:j], after removing consecutive sequences of
    // characters.
    // The optimal substructure can be defined as
    // dp[i][j] = min(
    //  min(dp[i][k], dp[k + 1][j]) for all i <= k < j,
    //  dp[i][j - 1] if s[i] == s[j]
    // )
    vector<vector<int>> dp(n, vector<int>(n, 0));

    // Base case: Substring of length 1
    for (int i = 0; i < n; ++i) {
      // Printing a character/sequence of same characters take 1 turn
      dp[i][i] = 1;
    }

    // Consider increasing lengths with different starting indices
    for (int len = 2; len <= n; ++len) {
      for (int i = 0; i + len - 1 < n; ++i) {
        int j = i + len - 1;

        // Start with the maximum possible length
        dp[i][j] = len;

        // For all possible splits between i and j
        for (int k = i; k < j; ++k) {
          int turns = dp[i][k] + dp[k + 1][j];

          // If the characters at i and j / start and end of the substring
          // matches, an extra turn can be saved
          dp[i][j] = min(dp[i][j], s[i] == s[j] ? turns - 1 : turns);
        }
      }
    }
    return dp[0][n - 1];
  }
};
