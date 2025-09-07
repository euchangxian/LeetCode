#include <vector>

class Solution {
 public:
  std::vector<int> sumZero(int n) {
    // Return any n unique integers that sum to 0.
    //
    // For even N, trivial, just pair with it's negative.
    // For odd N, trivial, reduce to even case by adding a zero.
    std::vector<int> result;
    result.reserve(n);
    if (n & 1) {
      result.emplace_back(0);
      --n;
    }

    for (int i = 0; i < n; i += 2) {
      result.emplace_back(i + 1);
      result.emplace_back(-(i + 1));
    }
    return result;
  }
};
