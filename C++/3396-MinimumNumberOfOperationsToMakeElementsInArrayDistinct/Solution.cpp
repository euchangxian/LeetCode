#include <bitset>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  int minimumOperations(std::vector<int>& nums) {
    // perform operation any number of times:
    // - remove 3 elements from the beginning of the array.
    // Empty array is considered distinct. But array of size 1 is also
    // considered distinct.
    // Seems recursive-like. Look at first 3, next 3, so on.
    // If there is a conflict, then remove the first 3.
    // Can be simplified!!
    // We know that we can only remove from the front. Thus, when iterating from
    // the back, if we encounter ANY duplicate, we need to remove all elements
    // up till and including that duplicate.
    // Thus, at index i, we need math.ceil(i+1 / 3) operations
    std::bitset<101> seen{};
    for (int i = nums.size() - 1; i >= 0; --i) {
      // i - start + 1 => number of elements including i.
      // ...+ 2 / 3 for ceiling division
      if (seen.test(nums[i])) {
        return (i + 1 + 2) / 3;
      }

      seen.set(nums[i]);
    }

    return 0;
  }
};
