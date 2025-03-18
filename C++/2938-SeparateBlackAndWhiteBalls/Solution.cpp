#include <cstddef>
#include <string>

class Solution {
 public:
  long long minimumSteps(std::string& s) {
    // 0-indexed string s of length n. 0 represents white balls, 1 represents
    // black balls.
    // In each step, two adjacent balls can be swapped.
    // Minimum steps to group all black balls to the right, all the white balls
    // to the left.
    //
    // Seems like a sorting problem. To move all the 1s to the right.
    // In each step, at most one '1' can be moved one step closer to the right,
    // i.e., right-shift or divide by 2.
    // Therefore, seems like a Counting problem too.
    // Count number of 1s?
    // Get the distance of each '1' from the right.
    // For each distance, minus (x-1) from the total steps for each '1', where
    // x is the number of '1's encountered so far.
    // This is because each '1' reduces the amount of right-shifts necessary
    // to effectively group the next '1' to the right.
    //
    // 100 -> 010 -> 001
    // 110 -> 101 -> 011
    // 1100 -> 1010 -> 1001 -> 0101 -> 0011.
    // 10101 -> 10011 -> 01011 -> 00111

    const std::size_t n = s.length();

    long long minOps = 0LL;
    int numOnes = 0;
    for (int i = n - 1; i >= 0; --i) {
      if (s[i] == '0') {
        continue;
      }

      minOps += ((n - 1 - i) - numOnes);
      ++numOnes;
    }
    return minOps;
  }
};
