#include <vector>

class Solution {
 public:
  int sumFourDivisors(std::vector<int>& nums) {
    // Return the sum of divisors of the integers that have exactly four
    // divisors.
    //
    // Each number already has 2 divisors: 1 and itself.
    // Therefore, if a number has exactly 4 divisors, then there must exist
    // exactly one divisor d, such that n % d == 0, and n % (n/d) == 0.
    int result = 0;
    for (auto x : nums) {
      int div = 0;
      for (auto d = 2L; d * d <= x; ++d) {
        if (x % d == 0) {
          if (div == 0) {
            div = d;
          } else {
            // multiple divisors
            div = 0;
            break;
          }
        }
      }

      if (div > 0 && div != x / div) {
        result += 1 + x + div + (x / div);
      }
    }
    return result;
  }
};
