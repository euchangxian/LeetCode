#include <algorithm>
#include <vector>

class Solution {
 public:
  std::vector<int> decimalRepresentation(int n) {
    std::vector<int> result;
    result.reserve(9);  // 1 <= n <= 1E9

    long long mult = 1;
    while (n) {
      auto d = mult * (n % 10);
      n /= 10;
      mult *= 10;

      if (d) {
        result.push_back(d);
      }
    }

    std::ranges::reverse(result);
    return result;
  }
};
