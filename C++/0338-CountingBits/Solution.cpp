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
 public:
  vector<int> countBits(int n) {
    vector<int> dp(n + 1);
    int mask = 1;
    for (int i = 1; i <= n; ++i) {
      if (mask << 1 == i) {
        mask = i;  // Set to all power of 2s
      }

      // Can visualise as increasing intervals
      // intervals: {0}, {1}, {2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11}
      // count:      0    1    1  2    1  2  3  4    1  2   3   4
      // where the count resets to 1 at the start of each power of 2
      dp[i] = dp[i - mask] + 1;
    }
    return dp;
  }
};
