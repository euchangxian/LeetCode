#include <cstddef>
#include <cstdlib>

class Solution {
 public:
  int minimizeXor(int num1, int num2) {
    // Same number of set bit as num2, but minimize XOR with num1.
    // Count the number of set bits in both num1 and num2.
    // The idea is to greedily set the bits in the result to '1' corresponding
    // to the set bits in num1.
    //
    // if n1 == n2, then return n1, where num1 ^ num1 == 0
    //
    // if n1 > n2, then let x be num1 with d = (n1-n2) LSBs cleared, to minimise
    //             num1 ^ x.
    //
    // if n1 < n2, then let x be num1 with its d=(n2-1) LSB unset bits set to
    //             '1'.
    //
    // Core of the problem is simple. How to implement cleanly?
    int n1 = __builtin_popcount(num1);
    int n2 = __builtin_popcount(num2);

    int result = num1;
    for (int i = 0; i < 32 && n1 != n2; ++i) {
      // If n1 > n2, then we want to clear the set bits.
      if (n1 > n2 && (num1 & (1 << i))) {
        result ^= (1 << i);
        --n1;
      }

      // if n2 > n1, then we want to set the unset bits.
      if (n2 > n1 && ((num1 & (1 << i)) == 0)) {
        result ^= (1 << i);
        --n2;
      }
    }

    return result;
  }
};
