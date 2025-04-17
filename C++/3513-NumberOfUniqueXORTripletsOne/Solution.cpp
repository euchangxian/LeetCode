#include <vector>

class Solution {
 public:
  int uniqueXorTriplets(std::vector<int>& nums) {
    // Given nums is a permutation from 1..n
    // Notice that we can always construct XOR values from 0..2^n-1
    // This is because we can simply take nums[i], nums[j] where either nums[i]
    // or nums[j] is odd, and 1.
    // Except for the edge case where n = 2, i.e., only 2 bits.
    // Not a rigorous proof.
    // Essentially, if we have more than 2 bits, we can control the value of any
    // bit.
    int n = nums.size();
    if (n <= 2) {
      return n;
    }

    return 1 << (32 - __builtin_clz(n));
  }
};
