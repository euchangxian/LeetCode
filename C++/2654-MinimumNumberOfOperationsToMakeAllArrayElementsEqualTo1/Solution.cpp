#include <algorithm>
#include <numeric>
#include <vector>

class Solution {
 public:
  int minOperations(std::vector<int>& nums) {
    //  given n positive integers.
    //  Operate any number of times:
    //  - select i such that 0<=i<n-1 and replace either nums[i] or nums[i+1]
    //    with their GCD value.
    // Return the minimum number of operations to make all elements equal to 1.
    // Otherwise -1.
    //
    // GCD(1, x) = 1.
    // if x, y are coprime, then GCD(x, y) = 1
    // nums.length <= 50 though.
    // Hm. if we have a 1, then we can make all elements equal to 1 with a
    // single operation each.
    // Otherwise, find a coprime adjacent pair, or a pair where x is a factor
    // of y or vice-versa. Thus, one operation to get a 1.
    const auto n = static_cast<int>(nums.size());
    int ones = 0;
    int gcd = 0;

    for (int x : nums) {
      ones += x == 1;
      gcd = std::gcd(gcd, x);
    }

    if (ones > 0) {
      return n - ones;
    }

    if (gcd > 1) {
      return -1;
    }

    int minLen = n;
    for (int i = 0; i < n; ++i) {
      int subGcd = 0;
      for (int j = i; j < n; ++j) {
        subGcd = std::gcd(subGcd, nums[j]);

        if (subGcd == 1) {
          minLen = std::min(minLen, j - i + 1);
          break;
        }
      }
    }
    return (minLen - 1) + (n - 1);
  }
};
