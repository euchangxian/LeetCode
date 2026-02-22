#include <algorithm>
#include <utility>

class Solution {
 public:
  int binaryGap(int n) {
    // Find the longest distance between any two adjacent 1s in the binary repr.
    // Return 0 otherwise.
    //
    // Can we treat this as an array question or are there bit tricks?
    // LSB, get index. repeat.
    int result = 0;
    auto prevIdx = 32;
    while (auto lsb = n & -n) {
      n ^= lsb;  // toggle off.
      auto idx = __builtin_ctz(lsb);
      result = std::max(result, idx - std::exchange(prevIdx, idx));
    }

    return result;
  }
};
