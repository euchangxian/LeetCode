class Solution {
 public:
  bool hasAlternatingBits(int n) {
    // Check if a number has alternating bits.
    //
    //   000101010 (n)
    // ^ 000010101 (n >> 1)
    // = 000111111 (check all 1s)
    //
    // Except, we shift 2 instead.
    //   000101010 (n)
    // ^ 000001010 (n >> 2)
    // = 000100000 (check power of 2)
    n ^= n >> 2;
    return !(n & (n - 1));
  }
};
