#include <array>

class Solution {
 public:
  double soupServings(int n) {
    // Two soups A and B starting with N ml. With equal chance, pour:
    // - 100ml from A, 0ml from B
    // - 75ml from A, 25ml from B
    // - 50ml from A, 50ml from B
    // - 25ml from A, 75ml from B
    // - If an operation requires pouring more than avavilable, then pour all.
    // Return the probability that A is used up before B, and 1/2 * the
    // probability that both A and B are used up in the same turn.
    //
    // is this maff.
    if (n >= 4725) {
      return 1.0;
    }

    std::array<std::array<double, 200>, 200> memo{};
    auto dfs = [&](this auto&& dfs, int a, int b) -> double {
      if (a <= 0 && b <= 0) {
        return 0.5;
      }

      if (a <= 0) {
        return 1.0;
      }

      if (b <= 0) {
        return 0.0;
      }

      auto& ans = memo[a][b];
      if (ans > 0) {
        return ans;
      }

      ans = 0.25 * (dfs(a - 4, b) + dfs(a - 3, b - 1) + dfs(a - 2, b - 2) +
                    dfs(a - 1, b - 3));
      return ans;
    };

    // (n+24)/25 => how many units of 25ml, since all operations are done
    // in units of 25ml.
    return dfs((n + 24) / 25, (n + 24) / 25);
  }
};
