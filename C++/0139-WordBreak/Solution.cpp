#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class Solution {
private:
public:
  bool wordBreak(string s, vector<string> &wordDict) {
    const size_t n = s.length();

    // Allow for quick lookup
    unordered_set<string> words(wordDict.begin(), wordDict.end());

    // Let dp[i] represent if the substring s[:i] can be made up with words
    // from the wordDict.
    vector<bool> dp(n + 1, false);
    dp[0] = true;

    // For each substring s[:i], there are two possible choices:
    // The whole substring s[:i] is in wordDict => dp[i] = true;
    // dp[j] == true AND the substring s[j:i] is in the wordDict => dp[i] = true

    // Minor optimization
    string sub;
    sub.reserve(n);
    for (int i = 1; i <= n; ++i) {
      s += s[i - 1];
      dp[i] = words.count(sub);
      for (int j = 0; j < n; ++j) {
        // i is 1-indexed. No need to add 1 i.e., i - j + 1
        dp[i] = dp[i] || (dp[j] && words.count(s.substr(j, i - j)));
      }
    }

    return dp[n];
  }
};
