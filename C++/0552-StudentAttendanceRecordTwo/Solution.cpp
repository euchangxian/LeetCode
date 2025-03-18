#include <vector>

class Solution {
 public:
  int checkRecord(int n) {
    const int MOD = 1000000007;
    // Maintain number of Absents, and number of consecutive Lates as state.
    // 0, or 1 Absent. 2 => no award.
    // 3 consecutive lates => no award
    // dp[numberOfDays][numberOfAbsents][numberOfConsecutiveLates]
    std::vector<std::vector<std::vector<int>>> dp =
        std::vector<std::vector<std::vector<int>>>(
            n + 1, std::vector<std::vector<int>>(2, std::vector<int>(3, 0)));

    // Base case when days = 0 => number of possible ways = 1
    dp[0][0][0] = 1;

    // Number of absent days cannot decrement!
    for (int day = 1; day < n + 1; ++day) {
      for (int totalAbsents = 0; totalAbsents < 2; ++totalAbsents) {
        for (int consecutiveLates = 0; consecutiveLates < 3;
             ++consecutiveLates) {
          // Choose "P". Reset consecutiveLates
          dp[day][totalAbsents][0] +=
              dp[day - 1][totalAbsents][consecutiveLates];
          dp[day][totalAbsents][0] %= MOD;

          // Choose "A" if totalAbsents + 1 < 2. Reset consecutiveLates
          if (totalAbsents + 1 < 2) {
            dp[day][totalAbsents + 1][0] +=
                dp[day - 1][totalAbsents][consecutiveLates];
            dp[day][totalAbsents + 1][0] %= MOD;
          }

          // Choose "L" if consecutiveLates + 1 < 3.
          if (consecutiveLates + 1 < 3) {
            dp[day][totalAbsents][consecutiveLates + 1] +=
                dp[day - 1][totalAbsents][consecutiveLates];
            dp[day][totalAbsents][consecutiveLates + 1] %= MOD;
          }
        }
      }
    }

    int result = 0;
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 3; ++j) {
        result += dp[n][i][j];
        result %= MOD;
      }
    }
    return result;
  }
};
