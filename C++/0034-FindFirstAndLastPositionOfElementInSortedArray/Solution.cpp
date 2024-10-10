#include <cstddef>
#include <vector>

using namespace std;
class Solution {
 public:
  vector<int> searchRange(vector<int>& nums, int target) {
    // Seems to be two binary searches. One for the lower bound, the other
    // for the upper bound.
    // In problem, we probably do not want to search for the instance where
    // nums[i] = target, but rather the first point in nums where
    // nums[i] < target. i.e. visualize nums as {F, F, F, T, T, T, T}
    // where F represents nums[i] < target, and the first T represents
    // nums[i] >= target.
    //
    // Similarly, {T, T, T, T, T, F, F} to find the other end of the range,
    // where the condition we want is nums[i] <= target.
    if (nums.empty()) {
      return {-1, -1};
    }

    const size_t n = nums.size();

    vector<int> range(2, -1);

    int start = 0;
    int end = n - 1;
    while (start < end) {
      int mid = start + (end - start) / 2;

      // Find the lower bound
      if (nums[mid] < target) {
        start = mid + 1;
      } else {
        end = mid;
      }
    }

    // Check that the lower bound is indeed target.
    if (nums[start] != target) {
      return {-1, -1};
    }
    range[0] = start;

    start = 0;
    end = n - 1;
    while (start < end) {
      int mid = start + (end - start + 1) / 2;  // Ceiling division

      if (nums[mid] <= target) {
        start = mid;
      } else {
        end = mid - 1;
      }
    }

    // There is no need to check that the upper bound is the target.
    // The earlier check would have returned early.
    range[1] = start;
    return range;
  }
};
