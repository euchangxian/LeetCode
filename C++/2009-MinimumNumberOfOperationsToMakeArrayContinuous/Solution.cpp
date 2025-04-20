#include <algorithm>
#include <vector>

class Solution {
 public:
  int minOperations(std::vector<int>& nums) {
    // In one operation, replace ANY element in nums with ANY integer.
    // nums is continuous if:
    // - All elements in nums are unique, and
    // - the difference between the maximum and minimum element in nums is
    //   nums.length - 1
    //
    // WLOG, consider the min element. Then, after determining the max element,
    // all duplicates and all elements greater than max incur one operation.
    // Is this sufficient?
    // Ah. We need to consider each element as the minimum instead.
    // Then, notice, if we sort the array, this becomes a max-length sliding
    // window where the max-min of the window is n-1.
    // Can be made O(N), if deques are used to keep the sliding window max,
    // and min. Ah. No. Cant keep track of duplicates...
    const int n = nums.size();
    std::sort(nums.begin(), nums.end());
    nums.erase(std::unique(nums.begin(), nums.end()), nums.end());

    int maxLength = 0;
    int l = 0;
    for (int r = 0; r < nums.size(); ++r) {
      // shrink window
      while (l < r && nums[r] - nums[l] > n - 1) {
        ++l;
      }
      maxLength = std::max(maxLength, r - l + 1);
    }

    return n - maxLength;
  }
};
