#include <string>
#include <vector>

class Solution {
 public:
  int numDecodings(std::string s) {
    if (s[0] == '0') {
      return 0;
    }

    int n = s.length();

    // dp[i] represents the number of ways to decode the first i characters of
    // the string
    // Since the maximum code is two digits, we only need to consider two
    // choices:
    // 1. decode 1 digit
    // 2. decode 2 digits.
    // For both cases, '0' cannot be leading
    std::vector<int> dp(n + 1, 0);
    dp[0] = 1;  // one way to decode 0 characters
    dp[1] = 1;  // the check above guarantees this is not a '0'.
    for (int i = 2; i < n + 1; ++i) {
      int oneDigit = s[i - 1] - '0';  // dp[i] is one-indexed
      int twoDigit = (s[i - 2] - '0') * 10 + oneDigit;

      if (oneDigit != 0) {
        dp[i] += dp[i - 1];
      }
      if (twoDigit >= 10 && twoDigit <= 26) {
        dp[i] += dp[i - 2];
      }
    }
    return dp[n];
  }
};
