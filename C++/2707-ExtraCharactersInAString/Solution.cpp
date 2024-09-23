#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution {
public:
  int minExtraChar(std::string s, std::vector<std::string> &dictionary) {
    const size_t n{s.length()};

    // Naively, let dp[i] represent the minimum extra characters left over by
    // breaking up s[:i].
    // Therefore, the minimum extra chars of s[:i] will be the minimum of
    // breaking up (s[:i-1] + 1), and dp[j] if s[j:i] is in the dictionary
    std::vector<int> dp(n + 1, n);
    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
      dp[i] = dp[i - 1] + 1;
      for (const std::string &word : dictionary) {
        if (i >= word.length() &&
            s.substr(i - word.length(), word.length()) == word) {
          dp[i] = std::min(dp[i], dp[i - word.length()]);
        }
      }
    }

    return dp[n];
  }
};
