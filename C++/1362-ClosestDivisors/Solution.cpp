#include <utility>
#include <vector>

class Solution {
 public:
  std::vector<int> closestDivisors(int num) {
    // Find two integers in absolute difference such that
    // x*y = num+1, or
    // x*y = num+2
    //
    // First glance seems like construction. Second glance, factorization?
    for (int i = std::sqrt(num + 2); i > 0; --i) {
      for (int n : {num + 1, num + 2}) {
        if (n % i == 0) {
          return {i, n / i};
        }
      }
    }
    std::unreachable();
  }
};
