#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdlib>
#include <numeric>
#include <vector>

constexpr int DIGITS = 10;
constexpr int MOD = 1e9 + 7;
std::array<std::vector<int>, DIGITS> adj{{
    {4, 6},
    {6, 8},
    {7, 9},
    {4, 8},
    {0, 3, 9},
    {},
    {0, 1, 7},
    {2, 6},
    {1, 3},
    {2, 4},
}};

class Solution {
 public:
  int knightDialerStateTransition(int n) {
    // Notice that the adjacency list is somewhat symmetrical.
    // 1 2 3
    // 4 5 6
    // 7 8 9
    // * 0 #
    // That is, that is, counting the state of certain cells is identical,
    // allowing us to group cells together.
    // Consider the following grouping:
    // A B A
    // C E C
    // A B A
    //   D
    // The corner cells are identical, in that it is reachable by 1B + 1C
    // B and C may seem symmetrical, but B is not reachable by D.
    // Thus, B is reachable by 2A, C is reachable by 2A + D,
    // D is reachable by 2C, E is isolated.
    // Therefore, aggregating the states (work through some concrete values to
    // better understand. The core idea is the number of ways to reach X cells
    // from Y):
    // - A = 2 * (B + C)  (each A cell can be reached by B/C cells in 2 ways)
    // - B = A (1 way to reach B from each A cell)
    // - C = A + (2 * D)
    // - D = C
    // - E = E
    // This greatly reduces the runtime, though still linear in growth.
    if (n == 1) {
      return DIGITS;
    }

    enum Group : std::size_t {
      A,
      B,
      C,
      D,
      SIZE,
    };

    std::array<int, Group::SIZE> group{{
        4,
        2,
        2,
        1,
    }};

    for (int i = 2; i <= n; ++i) {
      std::array<int, Group::SIZE> temp{};

      temp[A] = (2LL * (group[B] + group[C])) % MOD;
      temp[B] = group[A];
      temp[C] = (group[A] + (2LL * group[D])) % MOD;
      temp[D] = group[C];
      group = std::move(temp);
    }

    return std::reduce(
        group.begin(), group.end(), 0,
        [](int acc, int val) -> int { return (1LL * acc + val) % MOD; });
  }
  int knightDialer1D(int n) {
    // Space-optimized.
    // After the ith iteration, dp[j] represents the number of ways to make
    // i-length numbers ending with digit j.
    std::vector<int> dp(DIGITS, 1);
    for (int i = 2; i <= n; ++i) {
      std::vector<int> temp(DIGITS, 0);
      for (int j = 0; j < DIGITS; ++j) {
        for (int neighbour : adj[j]) {
          temp[j] = (1LL * temp[j] + dp[neighbour]) % MOD;
        }
      }
      dp = std::move(temp);
    }

    return std::reduce(dp.begin(), dp.end(), 0, [](int acc, int val) -> int {
      return (1LL * acc + val) % MOD;
    });
  }

  int knightDialer2D(int n) {
    // Given a 4 x 3 phone pad like:
    // 1 2 3
    // 4 5 6
    // 7 8 9
    // * 0 #
    // and a knight that can move in L shapes, determine the number of distinct
    // n-length numbers that can be dialed.
    // Naively, DFS. O(8^n), with a set to keep track of distinct numbers.
    // Can we do better?
    // Optimal Substructure seems to be rather straightforward.
    // Let dp[i][j] represents the number of ways to make a i-length number
    // ending with the digit j.
    // Then,
    // dp[i][j] = dp[i-1][x] for all x that are neighbours of i.
    // The adjacency list/graph can be preprocessed. Seems like at most two
    // neighbours given the Knight's movement.
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(DIGITS, 0));
    std::fill(dp[1].begin(), dp[1].end(), 1);
    for (int i = 2; i <= n; ++i) {
      for (int j = 0; j < DIGITS; ++j) {
        for (int neighbour : adj[j]) {
          dp[i][j] = (1LL * dp[i][j] + dp[i - 1][neighbour]) % MOD;
        }
      }
    }

    return std::reduce(
        dp[n].begin(), dp[n].end(), 0,
        [](int acc, int val) -> int { return (1LL * acc + val) % MOD; });
  }
};
