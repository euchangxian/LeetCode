#include <array>
class Solution {
 public:
  int maxProduct(int n) {
    std::array<int, 10> count{};
    while (n) {
      ++count[n % 10];
      n /= 10;
    }

    auto first = 0;
    for (int d = 9; d >= 1; --d) {
      if (count[d] == 0) {
        continue;
      }
      if (first) {
        return first * d;  // pair largest found so far with this digit
      }
      if (count[d] > 1) {
        return d * d;
      }
      first = d;
    }
    return 0;
  }
};
