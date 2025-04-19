class Solution {
 public:
  int minimumOneBitOperations(int n) {
    // Given an integer n <= 10^9, transform into 0 with the minimum number of
    // operations:
    // - Change the rightmost (0th) bit in the binary representation of n.
    // - Change the ith bit if the (i-1)th bit is 1, and the (i-2)th to 0th bit
    //   are set to 0.
    //   i.e., change the bit to the left of the rightmost '1' bit.
    // Note: "change" means changing to '1' so we can "move" a bit to the right.
    // The second operation always leaves a '1' bit.
    //
    // Hm. Consider powers of 2 (single set bit):
    // 0010 -> 0011 -> 0001 -> 0000 (3 ops)
    // 0100 -> 0101 -> 0111 -> 0110 -> 0010 -> 0011 -> 0001 -> 0000 (7 ops)
    // The pattern is clear with n=4, where we want to move "11" to the left,
    // up till the leading bit, then to the right.
    // NOTE: Tapped out. But from here, notice one very critical insight:
    // to get to 2^k, we need to first get to 2^(k-1), apply the second
    // operation, then get to 0. Recursively. (small note: we are taking for
    // granted, without proof, that the cost of transforming 0 to 2^k is the
    // same as transforming 2^k to 0. This is intuitive, since we can reverse
    // the operations to obtain the other, but a proof is necessary.)
    // Defining f as the cost, f(2^k) = f(2^(k-1)) + 1 + f(2^(k-1))
    //                                = 2 * f(2^(k-1)) + 1
    // At this point, we have shown f for powers of 2.
    // Reducing f further for this specific case, notice f(k) = 2^(k+1) - 1.
    // To solve f for a general x, we can therefore apply inclusion-exclusion.
    // Let k be the position of the most significant bit in x.
    // Then, f(x) = f(2^k) - f(x - 2^k) (minus, NOT plus!)
    // Since we have already derived a formula for f(2^k), we can recursively
    // solve this in O(log(log(n))) time, where the recursion depth is O(logN),
    // and each invocation takes O(logN) time (to count bits)
    //
    // How to deal with multiple bits?
    // 0101 -> ... (6 ops)
    // 0111 -> ... (5 ops)
    // 0110 -> ... (4 ops)
    // Though, from 0110, it seems removing leftmost bits first are optimal.
    // 0110 -> 0111 would be a regression.
    // DP? Whats the transition though, lol. Doesnt seem like there is a
    // "choice" to be made.
    //
    // Naively, we start from the leftmost bit.
    // If the bit to its right is '1', then add 1 to the required ops, remove
    // the leftmost bit and recurse.
    // Otherwise, hmmm. We want to reach a state where the right bit is '1'.
    if (n == 0) {
      return 0;
    }
    int k = 31 - __builtin_clz(n);
    return ((1 << (k + 1)) - 1) - minimumOneBitOperations(n - (1 << k));
  }
};
