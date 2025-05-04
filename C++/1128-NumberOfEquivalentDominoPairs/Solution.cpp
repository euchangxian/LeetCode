#include <array>
#include <vector>

class Solution {
 public:
  int numEquivDominoPairs(std::vector<std::vector<int>>& dominoes) {
    // dominoes[i] = [a, b] is equivalent to dominoes[j] = [c, d] iff
    // (a == c and b == d) OR (a == d and b == c) - that is one domino can be
    // rotated.
    // WLOG let a <= b. Then we can have a uniform way of checking pairs.
    // 1 <= dominoes[i][j] <= 9
    //
    // Hm. We can bitmask, since the order [a, b] does not matter
    int result = 0;
    std::array<int, 1 << 10> count{};
    for (const auto& domino : dominoes) {
      int mask = (1 << domino[0]) | (1 << domino[1]);
      result += count[mask]++;
    }
    return result;
  }
};
