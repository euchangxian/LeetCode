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
  int stoneGameII(vector<int>& piles) {
    // For the first move,
    // if Alice takes 1 pile, then Bob can take 1 or 2 piles
    // if Alice takes 2 piles, then Bob can take 1, 2, 3 or 4 piles
    //
    // For the third move (second move was Bob's),
    // if Bob took 1 pile, Alice can take 1 or 2 piles
    // if Bob took 2 piles, Alice can take 1, 2, 3, or 4 piles
    // if Bob took 3 piles, Alice can take 1, 2, ..., 6 piles
    // if Bob took 4 piles, Alice can take 1, 2, ..., 8 piles
    //
    // Overall, Alice's goal is to maximize her score, while minimizing Bob's
    // i.e., minimax algorithm.
    // Thus, instead of the score that Alice can get from taking the
    // first i piles, a different heuristic is needed to take into account
    // Bob's potential moves.
    // Since we want to consider the remaining possible scores achievable
    // after taking the first i piles, suffixSums should be used instead of
    // the usual prefix.
    int n = piles.size();

    // Calculate suffix sum
    vector<int> suffixSums = piles;
    for (int i = n - 2; i >= 0; --i) {
      suffixSums[i] += suffixSums[i + 1];
    }

    if (n <= 2) {
      // Base case is important to ensure indexing does not go out of bounds
      return suffixSums[0];
    }

    // dp[i][m] represents the number of stones the current player can get
    // starting from index i with a current value of M = m
    // m is 1-indexed. Therefore add one
    vector<vector<int>> dp(n, vector<int>(n, 0));

    // Loop from the back. Earlier states are dependant on future states.
    // For all combinations of i and m:
    for (int i = n - 1; i >= 0; --i) {
      for (int m = n - 1; m >= 1; --m) {
        if (i + 2 * m >= n) {
          dp[i][m] = suffixSums[i];
        }

        for (int x = 1; x <= 2 * m && i + x < n; ++x) {
          int opponent = dp[i + x][max(x, m)];
          dp[i][m] = max(dp[i][m], suffixSums[i] - opponent);
        }
      }
    }

    return dp[0][1];
  }

  int stoneGameIITopDown(vector<int> const& piles) {
    int n = piles.size();
    vector<int> suffix = piles;
    for (int i = n - 2; i >= 0; --i) {
      suffix[i] += suffix[i + 1];
    }

    // memo[idx][M] represents the number of stones obtainable by either player
    // at the idx-th index and with M possible piles to take.
    vector<vector<int>> memo(n, vector<int>(n, 0));
    return maxStones(suffix, 0, 1, memo);
  }

  int maxStones(vector<int> const& suffix,
                int idx,
                int m,
                vector<vector<int>>& memo) {
    if (idx + 2 * m >= suffix.size()) {
      // If the number of piles the current player can take is more than the
      // remaining number of piles, then take all the remaining piles.
      return suffix[idx];
    }

    if (memo[idx][m]) {
      // If this (idx, m) state has already been computed, return it
      return memo[idx][m];
    }

    // Otherwise, calculate the maximum number of stones achievable for the
    // next player.
    int nextPlayer = INT_MAX;

    // Recursively compute the maximum stones achievable by the next player.
    for (int x = 1; x <= 2 * m; ++x) {
      nextPlayer = min(nextPlayer, maxStones(suffix, idx + x, max(x, m), memo));
    }

    // For the current player, update the maximum stones obtainable
    memo[idx][m] = suffix[idx] - nextPlayer;
    return memo[idx][m];
  }
};
