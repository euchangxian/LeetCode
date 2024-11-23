#include <cstddef>
#include <cstdlib>

class Solution {
 private:
  double binaryExponent(double x, long long n) {
    // fast exponential:
    // n is even => (x * x)^(n/2)
    // n is odd => x * (x * x)^((n-1)/2)
    if (n == 0) {
      return 1;
    }

    if (n < 0) {
      return 1.0 / binaryExponent(x, -n);
    }

    if (n & 1) {
      return x * binaryExponent(x * x, (n - 1) / 2);
    }

    return binaryExponent(x * x, n / 2);
  }

 public:
  double myPow(double x, int n) {
    // handle the case where n = INT_MIN = -2`147`483`648.
    // when negated, will cause overflow.
    return binaryExponent(x, static_cast<long long>(n));
  }
};
