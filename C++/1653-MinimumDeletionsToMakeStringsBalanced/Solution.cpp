#include <algorithm>
#include <string>
#include <vector>

class Solution {
 public:
  int minimumDeletions(std::string s) {
    int n = s.length();

    // dp[i] represents the number of deletions required to balance
    // the substring s[0:i + 1]
    std::vector<int> dp(n + 1, 0);
    dp[0] = 0;

    // At each element, there are 2 choices, without loss of generality:
    // keep 'a' => that means to delete 'b', since there are more 'a's.
    // delete 'a' => keep 'b', since there are more 'b's
    int bees = 0;
    for (int i = 1; i < n + 1; ++i) {
      if (s[i - 1] == 'b') {
        dp[i] = dp[i - 1];
        ++bees;
        continue;
      }

      dp[i] = std::min(dp[i - 1] + 1, bees);
    }
    return dp[n];
  }
};
