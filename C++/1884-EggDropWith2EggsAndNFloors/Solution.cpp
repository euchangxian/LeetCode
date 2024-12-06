#include <algorithm>
#include <cstddef>
#include <vector>

class Solution {
 public:
  int twoEggDrop(int n) {
    // There exists a floor f such that any eggs dropped at a floor higher than
    // f will break, and any egg dropped at or below floor f will not break.
    //
    // From phrasing alone, seems like Binary Search is involved.
    // From experience, its DP!
    // For 2 eggs, the subproblems are straightforward.
    // Naively, drop egg at floor k.
    // 1. If break, then there are k - 1 floors to search (k-1 moves) with
    //    1 egg.
    // 2. No break, then k floors can be eliminated => n - k floors to search
    //    with 2 eggs.
    // Therefore, dp[i][j] represents the minimum number of moves to
    // determine with certainty the critical floor f with i eggs remaining
    // and j floors left.

    const int INF = 1000 + 1;

    // 2 eggs, n floors
    // Instead of initializing to INF, which would affect the subsequent
    // loop using std::max, set to 0 first.
    std::vector<std::vector<int>> dp(3, std::vector<int>(n + 1, 0));

    // base case
    for (int f = 0; f <= n; ++f) {
      // 1 egg, f floors means a linear search is necessary
      dp[1][f] = f;
    }

    // for each number of eggs
    for (int i = 2; i <= 2; ++i) {
      // for each number of floors
      for (int j = 1; j <= n; ++j) {
        dp[i][j] = INF;
        // Try dropping egg at each floor. However, instead of linearly building
        // the table from bottom up naively, notice that there is somewhat of
        // a monotonic property here. That is, as the floor that the egg is
        // dropped at increases:
        // 1. The number of moves required is non-decreasing if the egg breaks,
        //    as denoted by dp[i - 1][k - 1], where searching k - 1 floors with
        //    1 less egg is at least searching k floors + 1 move.
        // 2. The number of moves required is non-increasing if the egg does
        //    not break. Denoted by dp[i][j - k], where searching less floors
        //    with the same number of eggs allow for an at least
        //    better-than-linear number of moves.
        //
        // The key is to find the number of floors where these two monotonic
        // functions intersect, since we want the most minimum number of moves
        // to determine with CERTAINTY, i.e., the worse case.
        // I.e., think of it as finding the valley.
        //
        // Therefore, we can employ binary search to find valleys!
        int left = 1;
        int right = j;
        while (left < right) {
          int k = left + (right - left) / 2;

          int broken = dp[i - 1][k - 1];
          int notBroken = dp[i][j - k];

          // visualize the shape of the graphs
          if (broken < notBroken) {
            // means the k-th floor lie on the left of the valley.
            left = k + 1;
          } else {
            right = k;
          }
        }

        int worstCase = 1 + std::max(dp[i - 1][left - 1], dp[i][j - left]);
        dp[i][j] = std::min(dp[i][j], worstCase);
      }
    }
    return dp[2][n];
  }
};
