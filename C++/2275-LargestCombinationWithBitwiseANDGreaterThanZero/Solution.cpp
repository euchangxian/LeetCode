#include <algorithm>
#include <array>
#include <vector>

class Solution {
 public:
  int largestCombination(std::vector<int>& candidates) {
    // Consider two 1-bit numbers a and b. For the bitwise AND of the two to be
    // zero, i.e., a & b = 0, either a or b must be 0.
    // Therefore, for n k-bits (32 for int) numbers, the combined bitwise AND
    // of a subset will be 0 iff all the 1 bits are not common.
    // E.g. [16,17,71,62,12,24,14]
    // 16 = 0 0 1 0 0 0 0
    // 17 = 0 0 1 0 0 0 1
    // 71 = 1 0 0 0 1 1 1
    // 62 = 0 1 1 1 1 1 0
    // 12 = 0 0 0 1 1 0 0
    // 24 = 0 0 1 1 0 0 0
    // 14 = 0 0 0 1 1 1 0
    //
    // It is easy to see that the largest combination can be obtained from
    // comparing the i-th bit of each number and taking the position with the
    // most number of common bits; That combination will not be 0.
    //
    // Update: Improved cache locality by looping over candidates, then counting
    // the bit, instead of looping over each bit, then checking that bit for
    // each candidate.
    std::array<int, 32> bitCount{};
    for (int candidate : candidates) {
      int i = 0;
      int mask = 1;
      while (candidate > 0) {
        bitCount[i++] += candidate & mask;
        candidate >>= 1;
      }
    }

    return *std::max_element(bitCount.begin(), bitCount.end());
  }
};
