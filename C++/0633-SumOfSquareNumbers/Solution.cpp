#include <cmath>

class Solution {
 public:
  bool judgeSquareSum(int c) {
    // Given non-negative integer c, decide if there exists a and b such that
    // a^2 + b^2 = c
    //
    // c <= 2^31-1
    // seems like binary search:
    // a^2 = c - b^2
    // This reduces to find sqrt. Only if we do not have access to std::sqrt.
    using i64 = long long;
    for (auto b = 0LL; b * b <= c; ++b) {
      auto a = std::sqrt(c - b * b);
      // cast to int, which then gets promoted to double for comparison
      if (a == static_cast<int>(a)) {
        return true;
      }
    }
    return false;
  }
};
