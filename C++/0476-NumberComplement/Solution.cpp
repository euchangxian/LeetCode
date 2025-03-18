class Solution {
 public:
  int findComplement(int num) {
    // C++ bitwise-NOT will invert the leading 0 bits of a integer too.
    // E.g., int num = 128 = 0000 0000 ... 1000 0000
    // ~num = 1111 1111 ... 0111 1111
    // Whereas we are only interested in the last portion.
    // The number of bits in this portion is dictated by the most significant
    // '1' bit, which is the 25th MSB /8th LSB in this case
    // As such, a mask is required to mask the first 24 bits, then do a
    // bitwise-NOT
    unsigned mask = ~0;  // 1111 1111 ... 1111
    while (mask & num) {
      // shift the mask left until mask&num returns 0
      mask <<= 1;
    }

    // At this stage, the mask looks like 1111 1111 ... 0000 0000
    // Take the complement of the mask, and the number
    return ~mask & ~num;
  }
};
