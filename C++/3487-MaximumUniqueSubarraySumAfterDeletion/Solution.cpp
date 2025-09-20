#include <bitset>
#include <cstddef>
#include <limits>
#include <vector>

constexpr std::size_t MAX_VAL = 100;

class Solution {
 public:
  int maxSum(std::vector<int>& nums) {
    // Delete any number of elements from nums without making it empty.
    // Select a subarray such that:
    // - All elements are unique
    // - Sum is maximised.
    // Return the maximum sum.
    //
    // Simply remove all duplicates and negatives.
    // Or rather, count all distinct elements.
    std::bitset<MAX_VAL + 1> seen;

    int result = 0;
    int maxNegative = std::numeric_limits<int>::min();
    for (int x : nums) {
      if (x <= 0) {
        maxNegative = std::max(maxNegative, x);
        continue;
      }

      if (!seen[x]) {
        result += x;
      }
      seen.set(x);
    }
    return result == 0 ? maxNegative : result;
  }
};
