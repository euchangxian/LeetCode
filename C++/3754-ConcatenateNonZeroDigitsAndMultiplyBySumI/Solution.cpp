#include <array>

class Solution {
 public:
  long long sumAndMultiply(int n) {
    // Form a new integer x by concatenating all non-zero digits of n in
    // original order left to right.
    // Let sum be the sum of digits in x.
    // Return x*sum.
    std::array<int, 10> buff;
    auto idx = 0;

    auto sum = 0LL;
    while (n) {
      auto d = n % 10;
      n /= 10;
      if (d > 0) {
        buff[idx++] = d;
        sum += d;
      }
    }

    auto x = 0LL;
    while (idx--) {
      x = x * 10 + buff[idx];
    }
    return x * sum;
  }
};
