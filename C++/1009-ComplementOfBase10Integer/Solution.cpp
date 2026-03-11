#include <bit>
class Solution {
 public:
  int bitwiseComplement(int n) {
    // flip all the bits in binary.
    // e.g., 5 is 101, complement is 010 = 2
    if (n == 0) {
      return 1;
    }
    auto mask = (1 << std::bit_width(static_cast<unsigned int>(n))) - 1;
    return ~n & mask;
  }
};
