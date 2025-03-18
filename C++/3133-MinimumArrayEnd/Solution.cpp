#include <cstddef>
#include <cstdlib>

class Solution {
 public:
  long long minEnd(int n, int x) {
    // Construct array of positive integers where for every i in 0..n-1,
    // nums[i+1] is greater than nums[i], and the total bitwise AND of the
    // array is x.
    // Want: The minimum possible value of nums[n-1], i.e., the largest element
    // possible.
    // for bitwise AND, the result is at most equal or smaller than the minimum
    // of both numbers.
    // Suppose the inputs are always valid, then the first element must at least
    // already be x. Subsequent numbers must maintain the mask of x, plus some.
    // Thus, from this point, the minimum can be deduced. Suppose
    // x = 1101 0110. Then the first number has to be x.
    // There are n-1 remaining numbers. Then, the pattern starts from the
    // least significant unset bit;
    // i=1: 1101 0111,  i=2: 1101 1110
    // i=3  1101 1111,  i=4: 1111 0111, ...
    // Actually, not really a pattern. Its really just maintaining a counter
    // that starts from 1 and increments by 1, then for each bit in the counter,
    // disperse them to the unset bits.
    // e.g., x = 1101 0110
    // counter = 0000 0001
    // i=1 => x = 1101 0111, counter += 1 = 0000 0010
    // i=2 => x = 1101 1110, (the positions of the set bits in the counter are
    // adjusted to their relative positions in the next value.)
    // Therefore, there isnt actually a need to simulate. n-1 numbers remaining
    // mean that the counter will be n-1.
    // For each bit in the counter, set them into their relative positions
    // in x.
    // How to do this efficiently?
    // n = 3 = 0011 => counter = 2 = 0010
    // x = 4 = 0100 => minEnd = 0110
    unsigned long long counter = static_cast<long long>(n) - 1ULL;
    if (counter == 0) {
      return x;
    }

    // Only need to iterate up till the leading 1.
    int counterBits = 64 - __builtin_clzll(counter);

    long long minEnd = static_cast<long long>(x);
    int unsetBitPos = 0;
    for (int i = 0; i < counterBits; ++i) {
      // find the next unset bit in the current value.
      while (minEnd & (1LL << unsetBitPos)) {
        ++unsetBitPos;
      }

      // Regardless of whether the counter bit is 0 or 1, set the bit in the
      // correct position.
      minEnd |= ((counter & 1LL) << unsetBitPos);

      counter >>= 1;
      ++unsetBitPos;  // again, to avoid setting the current '0' bit again.
    }

    return minEnd;
  }
};
