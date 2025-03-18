#include <bitset>
#include <cstdint>

constexpr std::size_t kMaxChoices{1 << 20};  // 20 bits state
constexpr std::size_t kMaxTotal{300};

class Solution {
 public:
  bool canIWin(int maxChoosableInteger, int desiredTotal) {
    // Naively, there are [1..maxChoosableInteger] choices at each step.
    // DFS the tree and count the number of edges to reach desiredTotal.
    // Since we are assuming the role of the first person, the number of edges
    // should be odd-numbered, which indicates that the first player can force
    // a win.
    // Rather than edge-count, we can simply check the next state, whether it
    // is possible for that player to win. Starting from the first player,
    // we invert the bool result at each step.
    // Each integer from [1..maxChoosableInteger] can only be chosen once.

    if (desiredTotal <= maxChoosableInteger) {
      return true;
    }

    // Check that the total sum of all choices can reach the desiredTotal.
    const int maxPossibleSum =
        maxChoosableInteger * (maxChoosableInteger + 1) / 2;
    if (maxPossibleSum < desiredTotal) {
      // Both players cannot win.
      return false;
    }

    // memoized state, check whether the current state has been seen
    std::bitset<kMaxChoices> memo;
    return canWin(memo, desiredTotal, maxChoosableInteger, 0U);
  }

 private:
  // state is a bitset where each bit represents whether the integer from
  // the pool has already been chosen
  bool canWin(std::bitset<kMaxChoices>& memo,
              const int target,
              const int choices,
              uint32_t state) {
    if (memo.test(state)) {
      return memo[state];
    }

    if (target <= 0) {
      // Previous player already won.
      return false;
    }

    for (std::size_t choice{1}; choice <= choices; ++choice) {
      uint32_t choiceMask{1U << (choice - 1)};
      if (state & choiceMask) {
        continue;
      }

      // If the next player cannot win after making this choice, the current
      // player wins
      if (!canWin(memo, target - choice, choices, state | choiceMask)) {
        memo[state] = true;
        return true;
      }
    }

    // Reaching here means that all the remaining choices does not lead to a
    // win.
    memo[state] = false;
    return false;
  }
};
