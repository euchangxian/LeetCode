#include <limits>

constexpr int MAX_N = std::numeric_limits<int>::max();
constexpr int MAX_POW_THREE = []() {
  long long powThree = 1;
  while (true) {
    if (powThree * 3 > MAX_N) {
      break;
    }
    powThree *= 3;
  }

  return static_cast<int>(powThree);
}();

class Solution {
 public:
  bool isPowerOfThree(int n) {
    // determine if n is a power of 3, i.e., there exists x such that
    // n == 3^x.
    //
    // We can rule out negatives.
    if (n <= 0) {
      return false;
    }
    return (MAX_POW_THREE % n == 0);
  }
};
