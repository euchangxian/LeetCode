#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdlib>

constexpr int MAX_N = 10'000'000;
constexpr int MAX_POW = 14;

constexpr std::array<int, MAX_POW + 1> powers =
    []() -> std::array<int, MAX_POW + 1> {
  std::array<int, MAX_POW + 1> pow{};
  int x = 1;
  for (int i = 0; i < MAX_POW + 1; ++i) {
    pow[i] = x;
    x *= 3;
  }
  return pow;
}();

class Solution {
 public:
  bool checkPowersOfThree(int n) {
    // If the question was to check that a number is a sum of distinct powers of
    // 2, the answer would be trivially true for all n;
    // Simply look at its binary representation. We can construct the sums such
    // that each set bit is its own power of 2.
    // Is there an equivalent for powers of 3?
    // In base 3, each digit can be 0|1|2.
    // 220 => (2 * 3^2) + (2 * 3^1) + (0 * 3^0)
    // The key insight is that in base 3, we can determine if a number is a sum
    // of powers of 3 if the coefficients are all 0s and 1s (I believe this is
    // generalizable to base-b).
    //
    // A naive one would be to minus 3^k repeatedly, where  3^k is the largest
    // power of 3 such that n >= 3^k (LOL, turns out this is not so naive)
    // Can precompute powers of 3 first such that 3^k <= 10^7
    // Then, reduced to binary search on the power of 3, such that the end
    // result is 0.
    auto end = powers.end();
    while (n) {
      auto it = std::upper_bound(powers.begin(), end, n);
      if (it == powers.begin()) {
        return false;
      }

      --it;
      n -= *it;
      end = it;  // shrink
    }

    return true;
  }
};
