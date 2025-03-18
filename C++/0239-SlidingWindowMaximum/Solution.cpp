#include <deque>
#include <map>
#include <vector>

class Solution {
 public:
  std::vector<int> maxSlidingWindow(std::vector<int>& nums, int k) {
    std::vector<int> result;
    result.reserve(nums.size() - k + 1);

    // the max element must be kept at the front for amortized constant time
    // push/pop Since newer elements are added to the back of the deque, which
    // the window will cover for k iterations, we can remove any smaller
    // elements left in the deque, since they will never be considered the
    // window's maximum anymore. Since every element is added, and removed from
    // the deque exactly once, this solution runs in O(n) time.
    std::deque<int> dq;

    for (int i = 0; i < nums.size(); ++i) {
      if (!dq.empty() && dq.front() == i - k) {
        // remove index to the left of the window
        dq.pop_front();
      }

      // Maintain invariant.
      while (!dq.empty() && nums[i] >= nums[dq.back()]) {
        dq.pop_back();
      }
      dq.push_back(i);

      if (i >= k - 1) {
        // if the window is valid
        result.push_back(nums[dq.front()]);
      }
    }

    return result;
  }

  std::vector<int> maxSlidingWindowNLogN(std::vector<int>& nums, int k) {
    std::map<int, int> pq;
    for (int i = 0; i < k; ++i) {
      ++pq[nums[i]];
    }

    std::vector<int> maxSlidingWindow;
    maxSlidingWindow.reserve(nums.size() - k + 1);

    maxSlidingWindow.push_back(pq.rbegin()->first);  // largest element;
    for (int i = k; i < nums.size(); ++i) {
      if (!--pq[nums[i - k]]) {
        pq.erase(nums[i - k]);
      }
      ++pq[nums[i]];
      maxSlidingWindow.push_back(pq.rbegin()->first);
    }

    return maxSlidingWindow;
  }
};
