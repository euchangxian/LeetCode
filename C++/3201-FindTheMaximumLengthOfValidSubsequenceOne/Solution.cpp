#include <algorithm>
#include <array>
#include <vector>

class Solution {
 public:
  int maximumLength(std::vector<int>& nums) {
    // A subsequence sub of length x is valid if:
    // (sub[0]+sub[1])%2 == (sub[1]+sub[2])%2 == ... == (sub[x-2]+sub[x-1])%2
    // Return the length of the longest valid subsequence.
    //
    // i.e., sum of adjacent elements must all have the same parity.
    // odd+odd==even
    // even+odd==odd
    // odd+even==odd
    // even+even==even
    // With this, our subsequence must either alternate parities, or all have
    // the same parity.
    //
    // Therefore, we can maintain the count of odd/even, while maintaining the
    // longest alternating (zig-zag pattern)
    auto n = static_cast<int>(nums.size());

    std::array<int, 2> evenOdd{};
    int zigzag = 0;
    int previous = -1;
    for (int i = 0; i < n; ++i) {
      int parity = nums[i] & 1;
      ++evenOdd[parity];
      if (parity != previous) {
        ++zigzag;
        previous = parity;
      }
    }
    return std::max({evenOdd[0], evenOdd[1], zigzag});
  }
};
