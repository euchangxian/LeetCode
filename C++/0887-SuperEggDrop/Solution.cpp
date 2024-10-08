#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <cstdint>
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
  // Returns the minimum number of moves to determine with certainty the
  // critical floor f_c, given two eggs.
  //
  // An egg dropped above any floor higher than the critical floor f_c will
  // break, while an egg dropped on or below the critical floor f_c will not
  // break and can be reused.
  //
  // Suppose the minimum number of moves to determine f_c given two eggs is x.
  // Then, the claim is that the first floor to drop the egg from cannot exceed
  // x.
  //
  // Proof (by contradiction):
  //  1. Suppose for the sake of contradiction that the first floor picked
  //     exceeds x. That is pick x + 1.
  //  2. Then, there are two possible cases:
  //     2.1.   Case 1: Egg breaks
  //     2.1.1. Then, for the critical floor to be found with certainty, the
  //            remaining egg has to be dropped sequentially from floor 1, till
  //            floor x.
  //     2.1.2. This linear search takes x steps. Combined with the 1 step
  //            from dropping the first egg at floor x + 1, the total number of
  //            moves to find the critical floor is x + 1, which contradicts
  //            the claim.
  //  3. Thus, given two eggs, the claim that the first floor picked cannot
  //     exceed x holds true.
  //
  // Generalizing it to k number of eggs, the claim is that there exists an
  // Optimal Substructure such that
  // Given k eggs and n floors:
  // Suppose an egg is dropped at floor x, the minimum number of moves to
  // determine f_c is the minimum of the maximum (certainty i.e. worst case)
  // between:
  //  1. the minimum number of moves to deterimne f_c with (k - 1) eggs and
  //     (x -1) floors, and (egg breaks)
  //  2. the minimum number of moves to determine f_c with k eggs and (n - x)
  //     floors. (egg does not break)
  //
  int superEggDrop(int k, int n) {
    constexpr int INF = 10e5;
    // Cheeky reference to past proof for 2 Eggs and N floors.

    // dp[k][n] represents the minimum number of moves to determine with
    // certainty the critical floor, with k eggs and n floors.
    vector<vector<int>> dp(k + 1, vector<int>(n + 1, 0));

    // base case: 1 egg, n floor requires n trials (linear search)
    for (size_t i{1}; i <= n; ++i) {
      dp[1][i] = i;
    }

    // For each number of eggs and floors
    for (int eggs = 2; eggs <= k; ++eggs) {
      for (int floors = 1; floors <= n; ++floors) {
        dp[eggs][floors] = INF;

        // As the floor that the egg is dropped from increases,
        // there are two different monotonic functions:
        // 1. Egg breaks: The number of moves then to determine the critical
        //    floor is monotonically increasing.
        // 2. Egg does not break: The number of moves to determine the critical
        //    floor is monotonically decreasing.
        // function starts off higher
        // Given that the broken function starts off lower, then increases,
        // while the notBroken starts high, then decreases.
        int start{1};
        int end{floors};
        while (start <= end) {
          const int floor = start + (end - start) / 2;

          // Can only eliminate the current floor. Critical floor is below
          const int broken = dp[eggs - 1][floor - 1];

          // Can eliminate the bottom x floors from consideration. The
          // critical floor lies above
          const int notBroken = dp[eggs][floors - floor];

          // Need to determine with certainty. Both choices involve throwing
          // an egg, i.e. 1 step
          const int worstCase = std::max(broken, notBroken) + 1;

          // Take the best of the worst
          dp[eggs][floors] = std::min(dp[eggs][floors], worstCase);

          if (broken < notBroken) {
            start = floor + 1;
          } else {
            end = floor - 1;
          }
        }
      }
    }
    return dp[k][n];
  }
};
