#include <algorithm>
#include <cstddef>
#include <vector>

using namespace std;
class Solution {
 public:
  int maxWidthRamp(vector<int>& nums) {
    // Naively, we would check every pair (i, j) and get the longest width that
    // fulfils the constraints. O(n^2)
    // How can we do better?
    //
    //
    // If nums is strictly decreasing, then there will be no ramp
    // Sliding window? Move right, calculate width j - i. If nums[j] < nums[i],
    // then shrink the window.
    // 9 8 1 0 1 9 4 0 4 1
    // ^       ^           width = 5
    //   ^       ^         width = 5
    //     ^       ^       width = 5
    // NOPE. The elements in between i and j does not have to be monotonic.
    // Therefore, the condition for shrinking the window is flawed.
    //
    // For a given i/nums[i], we can stop checking if we know that the elements
    // after it are less than nums[i].
    // Therefore, we can do pre-processing to figure out the suffixMax.
    // This will give us the necessary conditions to shrink the window.
    //
    // For nums = 9 8 1 0 1 9 4 0 4 1,
    // suffixMax= 9 9 9 9 9 9 4 4 4 1.
    //            ^           ^         nums[l] = 9 > suffixMax[r] = 4. Shrink.
    //                ^       ^         No more nums[r] >= nums[l] = 9 exists.
    //                ^             ^   right ptr advances till end.
    // Therefore, the answer will be r - l = 9 - 2 = 7.

    const size_t n = nums.size();

    // suffixMax[i] is the maximum nums to the right of i, including nums[i]
    vector<int> suffixMax(n);
    suffixMax[n - 1] = nums[n - 1];
    for (int i = n - 2; i >= 0; --i) {
      suffixMax[i] = max(suffixMax[i + 1], nums[i]);
    }

    int width = 0;
    int l = 0;
    for (int r = 0; r < n; ++r) {
      // If the start of the window is greater than the suffixMax at the end of
      // the window, then we know that the condition nums[i] <= nums[j] will
      // never be fulfilled from this point onwards, and we can shrink the
      // window.
      while (l < r && nums[l] > suffixMax[r]) {
        ++l;
      }
      width = max(width, r - l);
    }

    return width;
  }
};
