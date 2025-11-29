#include <algorithm>
#include <functional>
#include <vector>

class Solution {
 public:
  int minOperations(std::vector<int>& nums, int k) {
    // perform any number of times:
    // - select an index i, replace nums[i] with nums[i] - 1
    // Return minimum operations to make sum of the array divisible by k.
    //
    // Each operation decreases the sum by -1.
    // Just get total sum.
    auto sum = std::ranges::fold_left(nums, 0, std::plus<>{});
    return (sum % k);
  }
};
