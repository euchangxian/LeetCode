#include <cstddef>
#include <vector>

using namespace std;
class Solution {
 public:
  int findPeakElement(vector<int>& nums) {
    // Find Peaks!
    // A peak is an element that is greater than its neighbours. e.g., for
    // any index i in [0..n], nums[i] is a peak iff
    // nums[i-1] < nums[i] > nums[i + 1]
    // It seems that we just need to find local peaks/maximas, given that
    // this is not a "rotated" sorted array.
    // Therefore, depending on the gradient, we can decide which direction to
    // search.
    // if peak, i.e., nums[i-1] < nums[i] > nums[i + 1], then return i.
    // if increasing gradient, i.e., nums[i-1] <= nums[i] <= nums[i+1],
    // then search right.
    // if decreasing gradient, i.e,  nums[i-1] >= nums[i] >= nums[i+1],
    // then search left.
    // There will always be peaks, given that elements are always considered
    // greater than its neighbours.
    int n = nums.size();

    int left = 0;
    int right = n - 1;
    while (left < right) {
      int mid = left + (right - left) / 2;

      if (nums[mid] <= nums[mid + 1]) {
        // Decreasing slope, go right
        left = mid + 1;
      } else {
        right = mid;
      }
    }
    return left;
  }
};
