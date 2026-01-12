#include <deque>
#include <vector>

class Solution {
 public:
  int longestSubarray(std::vector<int>& nums, int limit) {
    // Return the size of the longest non-empty subarray such that the absolute
    // difference between any two elements of this subarray is <= limit.
    //
    // Feels like a std::multiset to maintain a sorted ordering of the
    // window, so we can binary search with lower/upper_bound to check the
    // difference.
    // nlogn.
    //
    // Can we do better?
    // Ah. We dont need to track each element and its adjacents in the sorted
    // window.
    // Just track the min/max.
    // Monotonic Deques.
    const auto n = static_cast<int>(nums.size());
    int result = 0;

    std::deque<int> windowMax;
    std::deque<int> windowMin;
    for (int l = 0, r = 0; r < n; ++r) {
      while (!windowMax.empty() && windowMax.back() < nums[r]) {
        windowMax.pop_back();
      }
      windowMax.push_back(nums[r]);

      while (!windowMin.empty() && windowMin.back() > nums[r]) {
        windowMin.pop_back();
      }
      windowMin.push_back(nums[r]);

      while (windowMax.front() - windowMin.front() > limit) {
        if (windowMax.front() == nums[l]) {
          windowMax.pop_front();
        }

        if (windowMin.front() == nums[l]) {
          windowMin.pop_front();
        }
        ++l;
      }

      result = std::max(result, r - l + 1);
    }

    return result;
  }
};
