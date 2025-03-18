#include <cstddef>
#include <cstdlib>
#include <stack>
#include <vector>

class Solution {
 public:
  std::vector<int> maximumLengthOfRanges(std::vector<int>& nums) {
    // seems like monotonic-decreasing stack to me.
    // When popping from the stack, i.e., a larger element at index j is seen,
    // the length of the range can be calculated.
    const std::size_t n = nums.size();
    std::vector<int> lengths(n, 0);
    std::stack<int> maxWindow;
    for (int i = 0; i < n; ++i) {
      // maintain decreasing property:
      while (!maxWindow.empty() && nums[i] > nums[maxWindow.top()]) {
        int top = maxWindow.top();
        maxWindow.pop();

        // if empty, that means that the element is the biggest element of the
        // prefix [0..j)
        int prev = maxWindow.empty() ? -1 : maxWindow.top();
        lengths[top] = i - prev - 1;
      }

      maxWindow.push(i);
    }

    // handle decreasing subarrays that end at the last element.
    while (!maxWindow.empty()) {
      int top = maxWindow.top();
      maxWindow.pop();

      int prev = maxWindow.empty() ? -1 : maxWindow.top();
      lengths[top] = n - prev - 1;
    }
    return lengths;
  }
};
