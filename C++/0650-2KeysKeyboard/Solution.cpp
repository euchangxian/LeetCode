#include <algorithm>
#include <vector>

class Solution {
 public:
  const int LIMIT = 1001;
  int minSteps(int n) {
    // dp[i] represents the minimum number of operations required to get the
    // character 'A' exactly i times on the screen
    // To get each length i, mutiple choices can be made:
    // 1. Copy i/2 and paste once.
    // 2. Copy i/3 and paste twice
    // 3. ...
    // 4. Copy i/i and paste i-1 times.
    //
    // Approach seems to be, for each i, multiply by j, such that i*j < n + 1,
    // and take the min number of steps.
    // dp[1] = 0
    // dp[2] = 2 (copy 1, paste 1)
    // dp[3] = 3 (copy 1, paste 1, paste 1)
    // dp[4] = 4 (copy 1, paste 1, then copy 2, paste 2, or paste 1, paste 1)
    // dp[5] = 5 (copy 1, paste 1, paste 1, paste 1, paste 1)
    // dp[6] = 5 (copy 1, paste 1, copy 2, paste 2, paste 2)
    // dp[7] = 7 (copy 1, paste 1, paste 1, paste 1, paste 1, paste 1, paste 1)
    //
    // Notice that prime numbers have no factors, and thus, dp[prime] = prime
    // Though this will require a mathematical approach.
    // DP approach is more generalizable.
    // n <= 1000. The maximum steps to get 1000 length is by copy and pasting a
    // length of 1. Prevents overflow in later steps
    std::vector<int> dp(n + 1, LIMIT);
    dp[0] = 0;  // 0 operations to get 0 characters
    dp[1] = 0;  // Start with one character on the screen

    for (int i = 2; i < n + 1; ++i) {
      // Enumerate over choices
      for (int j = 1; j <= i; ++j) {
        if (i % j) {
          continue;  // length i is not divisible by j
        }
        // steps to get j length, and additional
        // copy + paste steps = i/j
        dp[i] = std::min(dp[i], dp[j] + i / j);
      }
    }

    return dp[n];
  }
};
