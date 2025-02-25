#include <array>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  int numOfSubarrays(std::vector<int>& arr) {
    // even - odd = odd
    // odd - even = odd
    // Prefix sums, maintain count of even and odd prefix sums?
    // Thus, when iterating through, if the prefix sum is even, then add
    // the count of all odd prefixes
    // Otherwise, add the count of all even prefixes.
    constexpr int MOD = 1000000007;

    // {even, odd}, indexed using bitmask AND
    std::array<int, 2> count{{1, 0}};
    int total = 0;
    int prefix = 0;
    for (int num : arr) {
      prefix += num;

      // if odd, add even count, i.e., count[0]
      // else add count[1]
      total = ((1LL * total) + count[1 - (prefix & 1)]) % MOD;
      ++count[prefix & 1];
    }
    return total;
  }
};
