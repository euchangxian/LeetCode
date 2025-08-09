class Solution {
 public:
  bool isPowerOfTwo(int n) {
    // Need to handle n = INT_MIN
    // Also, question mentions - satisfy: n == 2^x
    // Thus, all negatives are ruled-out.
    return n > 0 && (n & (n - 1)) == 0;
  }
};
