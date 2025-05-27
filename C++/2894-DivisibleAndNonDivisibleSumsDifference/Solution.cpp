#include <array>

class Solution {
 public:
  int differenceOfSums(int n, int m) {
    // num1: sum of all integers in the range [1..n] that are NOT divisble by m
    // num2: sum of all integers in the range [1..n] that are divisble by m
    // return num1-num2
    std::array<int, 2> num{};
    for (int i = 1; i <= n; ++i) {
      num[static_cast<bool>(i % m == 0)] += i;
    }
    return num[0] - num[1];
  }
};
