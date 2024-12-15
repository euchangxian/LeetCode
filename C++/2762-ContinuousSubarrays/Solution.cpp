#include <cstddef>
#include <cstdlib>
#include <deque>
#include <vector>

class Solution {
 public:
  long long continuousSubarrays(std::vector<int>& nums) {
    // for each pair of indices,
    // i <= i_1, i_2 <= j,
    // 0 <= | nums[i_1] - nums[i_2] | <= 2
    // i.e., for each subarray, every pair of numbers in the subarray must
    // have a difference of less than or equal to 2 for it to be continuous.
    // backtracking? input constraints imply unlikely though.
    // Seems tough. Something like a minmax sliding window. hm.
    // Sort?? delulu. Cant mutate the input.
    // Hm. Notice that sliding window was indeed a correct intuition.
    // We can advance the right pointer till we find an element j that violates
    // the difference property, maintaining the maximum/minimum from [i..j].
    // Advance the left pointer otherwise.
    // The number of subarrays within [i..j] would then be k * (k-1)/2, where k
    // is the number of elements. However, since we increment the count from
    // [i..j], [i..k], ..., (i.e., the left elements are included multiple
    // times), we want to reframe this as the number of pairs made by adding
    // the right-most element, which is simply the count of the subarray.
    // How do we maintain the min/max then? Monotonic Deques would work.

    // Maintain indices instead of elements, so we can cleanup expired elements
    // easily.
    std::deque<int> maxWindow;  // Monotonically decreasing
    std::deque<int> minWindow;  // Monotonically increasing

    long long count = 0LL;
    int l = 0;
    for (int r = 0; r < nums.size(); ++r) {
      // add current element to respective min/maxes.
      while (!maxWindow.empty() && nums[r] > nums[maxWindow.back()]) {
        maxWindow.pop_back();
      }
      maxWindow.push_back(r);

      while (!minWindow.empty() && nums[r] < nums[minWindow.back()]) {
        minWindow.pop_back();
      }
      minWindow.push_back(r);

      // shrink window if the min-max diff exceeds 2.
      while (!maxWindow.empty() &&
             nums[maxWindow.front()] - nums[minWindow.front()] > 2) {
        // move the left pointer to the element that violates the condition,
        // i.e., the left-most index.
        if (maxWindow.front() < minWindow.front()) {
          l = maxWindow.front() + 1;
          maxWindow.pop_front();
        } else {
          l = minWindow.front() + 1;
          minWindow.pop_front();
        }
      }

      count += r - l + 1;
    }

    return count;
  }
};
