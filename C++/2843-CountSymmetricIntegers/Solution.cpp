#include <array>

constexpr int MAX_N = 1e4;
constexpr auto symmetric = [](int n) {
  if (n < 10 || (n >= 100 && n < 1000) || n >= 10000) {
    return false;
  }

  int idx = 0;
  std::array<int, 4> digit{};
  while (n) {
    int d = n % 10;
    n /= 10;
    digit[idx++] = d;
  }

  if (idx == 2) {
    return digit[0] == digit[1];
  }
  return (digit[0] + digit[1]) == (digit[2] + digit[3]);
};

constexpr std::array<int, MAX_N + 1> COUNT = []() {
  std::array<int, MAX_N + 1> dp{};

  for (int n = 1; n <= MAX_N; ++n) {
    dp[n] = dp[n - 1] + symmetric(n);
  }
  return dp;
}();

class Solution {
 public:
  int countSymmetricIntegers(int low, int high) {
    // Compile time fun.
    return COUNT[high] - COUNT[low - 1];
  }

  int countSymmetricIntegersLogN(int low, int high) {
    // A number x consisting of 2*n digits is symmetric if the sum of the first
    // n digits of x is equal to the last n digits of x.
    // Note the constraints: 1 <= low <= high <= 10^4
    // Thus, each number in has at most 4 digits, and checking symmetry can be
    // done in "constant" time.
    // Can prune away odd sections.
    int count = 0;
    for (int n = low; n <= high; ++n) {
      if (n < 10) {
        n = 9;
      } else if (n >= 100 && n < 1000) {
        n = 999;
      } else if (n >= 10000) {
        n = 99999;  // not really necessary, since high<=10^4
      } else {
        count += symmetric(n);
      }
    }
    return count;
  }
};
