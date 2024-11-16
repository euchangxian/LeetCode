#include <cstddef>
#include <cstdlib>
#include <deque>
#include <vector>

class Solution {
 public:
  std::vector<int> resultsArray(std::vector<int>& nums, int k) {
    // nums of length n, integer k.
    // Power is defined as:
    // its maximum element if all its elements are consecutive and ascending.
    // -1 otherwise.
    // Find power of all subarrays of size k.
    // Fixed size sliding window/max deque?
    //
    // See element, add to deque. Should add index instead of value, so that
    // we know when to remove the leftmost.
    // When adding to the back, while the back element is smaller, pop
    // and remove it, since we want max Deque.
    // The front of the window should be the maximum of the current window.
    //
    // How to handle non-increasing?
    // Hmmm, not sure if max-Deque is necessary. Can we exploit the consecutive
    // and increasing order requirement?
    std::vector<int> result;
    result.reserve(nums.size() - k + 1);

    std::deque<int> maxWindow;
    for (int r = 0; r < nums.size(); ++r) {
      // book-keep, remove from left if size is more than k
      // equivalent to (r - l + 1) > k
      if (!maxWindow.empty() && maxWindow.front() == r - k) {
        maxWindow.pop_front();
      }

      // max deque, maintain invariant where the deque is monotonically
      // increasing. HOWEVER, we can simply it here. IF the element in the
      // window is NOT consecutive AND NOT smaller, i.e, back + 1 != nums[r]
      // Then, the entire window is invalid.
      if (!maxWindow.empty() && nums[maxWindow.back()] + 1 != nums[r]) {
        maxWindow.clear();
      }
      maxWindow.push_back(r);

      // check for windows of size k
      if (r >= k - 1) {
        if (maxWindow.size() == k) {
          // the back element is the max instead.
          result.push_back(nums[maxWindow.back()]);
        } else {
          result.push_back(-1);
        }
      }
    }
    return result;
  }
};
