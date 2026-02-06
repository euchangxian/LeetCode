#include <algorithm>
#include <vector>

class Solution {
 public:
  int minRemoval(std::vector<int>& nums, int k) {
    // An array is considered balanced if it's maximum element is at most k
    // times the minimum element.
    // Remove any number of elements without making it empty.
    // Return the mininum number of removals required.
    //
    // Seemingly, sort. But not so straightforward?
    // We can remove from the left or right, but one path may be faster.
    // e.g., nums={1,2,3,4,100}, k=4
    // Just try each starting point.
    // the second pointer does not need to be reset each time.
    // NOTE: we can reduce the problem further to find the max window such that
    // nums[r] > nums[l]*k is fulfilled.
    using i64 = long long;

    const auto n = static_cast<int>(nums.size());
    std::ranges::sort(nums);

    int result = n - 1;
    int r = 0;
    for (int l = 0; l < n; ++l) {
      while (r < n &&
             static_cast<i64>(nums[l]) * k >= static_cast<i64>(nums[r])) {
        ++r;
      }
      result = std::min(result, n - (r - l));
    }
    return result;
  }
};
