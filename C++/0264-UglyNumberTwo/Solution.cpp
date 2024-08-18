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
  int nthUglyNumber(int n) {
    // dp[i] represents the i-th ugly number (1-indexed)
    // Optimal Substructure: Each ugly number is generated from a previous ugly
    // number by multiplying it by either 2, 3, or 5
    vector<int> dp(n);
    dp[0] = 1;

    int i2 = 0;
    int i3 = 0;
    int i5 = 0;

    for (int i = 1; i < n; ++i) {
      int nextUgly = min(dp[i2] * 2, min(dp[i3] * 3, dp[i5] * 5));

      dp[i] = nextUgly;

      // Move the pointers forward if they were used to generate the current
      // ugly number
      // This also ensures no duplicates are generated
      if (dp[i2] * 2 == nextUgly) {
        ++i2;
      }

      if (dp[i3] * 3 == nextUgly) {
        ++i3;
      }

      if (dp[i5] * 5 == nextUgly) {
        ++i5;
      }
    }
    return dp[n - 1];
  }
};
