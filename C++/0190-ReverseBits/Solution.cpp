#include <cstdint>

class Solution {
 public:
  uint32_t reverseBits(uint32_t n) {
    int result = 0;

    for (int i = 0; i < 32; ++i) {
      // Left shift result, then add the right-most bit of n
      result = (result << 1) + ((n >> i) & 1);
    }
    return result;
  }
};
