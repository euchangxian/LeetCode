class Solution {
 public:
  int makeTheIntegerZero(int num1, int num2) {
    // In one operation, choose i in the range [0..60] and subtract 2^i + num2
    // from num1.
    // Return the minimum number of operations to make num1 equal to 0.
    // If impossible, return -1.
    //
    // Note that -10E9 <= num2 <= 10E9
    // The number of '1' bits in num1 is the upper-bound on the number of
    // operations we need to perform if num2 is positive, and the lower-bound
    // elsewise.
    // Binary Search? Doesnt seem possible if num2 is negative. There is no
    // monotonic property that is obvious.
    for (long long k = 1LL; k <= 60LL; ++k) {
      long long target = num1 - (k * num2);
      if (target < k) {
        return -1;
      }

      if (__builtin_popcountll(target) <= k) {
        return k;
      }
    }
    return -1;
  }
};
