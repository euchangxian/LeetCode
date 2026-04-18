#include <cmath>

class Solution {
 public:
  int mirrorDistance(int n) {
    // Define mirror distance as: abs(n - reverse(n)) where reverse(x) is formed
    // by reversing the decimal digits of n.
    constexpr auto reverse = [](auto n) {
      auto result = 0;
      while (n) {
        auto d = n % 10;
        n /= 10;
        result = result * 10 + d;
      }
      return result;
    };
    return std::abs(n - reverse(n));
  }
};
