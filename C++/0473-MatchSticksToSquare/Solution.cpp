#include <algorithm>
#include <array>
#include <functional>
#include <numeric>
#include <vector>

using i64 = long long;
class Solution {
 public:
  bool makesquare(std::vector<int>& matchsticks) {
    // matchsticks[i] is the length of the ith matchstick. Use all matchsticks
    // to make a square.
    // Return true if possible, false otherwise.
    //
    // Greedy wouldnt work trivially
    // e.g., {1, 1, 3, 4, 4, 5, 7, 8}
    // taking from left while sum < side will fail.
    //
    // 2 pointers?
    // Not necessary too. Consider arbitrarily taking left first.
    // E.g., {1, 1, 3, 5, 7, 7, 8}
    // sides = {1, 7}, {1, 7}, {8}, {3, 5}
    // greedy= {1, 1, 3}, ... fail.
    //
    // DP?
    // 4 sides. Base case when i == n indicating all sticks considered already,
    // and sides == 4, not more, not less.
    // Can prune when sides >= 4 and i < n otherwise.
    // Hm. Order does matter in this way. Maintain an array of 4, indicating
    // the length of each side? Then add to each and recurse on the choice.
    // Backtracking.
    // Need to prune.
    if (matchsticks.size() < 4) {
      return false;
    }

    // try larger sticks first to branch less.
    std::ranges::sort(matchsticks, std::greater<>{});
    i64 total =
        std::reduce(matchsticks.begin(), matchsticks.end(), 0LL, std::plus<>{});
    if (total % 4 != 0) {
      return false;
    }

    i64 target = total / 4;
    if (matchsticks.front() > target) {
      return false;
    }
    std::array<i64, 4> sides{};
    return dfs(matchsticks, target, sides, 0);
  }

 private:
  bool dfs(std::vector<int>& matchsticks,
           i64 target,
           std::array<i64, 4>& sides,
           int idx) {
    if (idx >= matchsticks.size()) {
      return std::ranges::all_of(sides,
                                 [target](i64 x) { return x == target; });
    }

    for (int i = 0; i < sides.size(); ++i) {
      // prune if adding to this side exceeds.
      if (sides[i] + matchsticks[idx] > target) {
        continue;
      }

      // prune if equal length to any earlier sides. No need to
      // try this branch.
      bool same = false;
      for (int j = i - 1; j >= 0; --j) {
        if (sides[i] == sides[j]) {
          same = true;
          break;
        }
      }

      if (same) {
        continue;
      }

      sides[i] += matchsticks[idx];
      if (dfs(matchsticks, target, sides, idx + 1)) {
        return true;  // prune early
      }
      sides[i] -= matchsticks[idx];
    }
    return false;
  }
};
