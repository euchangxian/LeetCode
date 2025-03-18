#include <climits>
#include <cstddef>
#include <stack>
#include <vector>

class Solution {
 public:
  int validSubarraySize(std::vector<int>& nums, int threshold) {
    // First glance looks like a sliding window.
    // {2, 3, 4, 3, 1}, threshold = 8
    // Adjusting the window size is not straightforward though.
    //
    // There is a monotonic property, where the threshold/k decreases as k
    // increases. Thus, if we can determine that an element, even if included,
    // will never exceed threshold/k, then we can exclude it.
    //
    // For starters, determine threshold/nums.size. If an element is smaller
    // than it, then it should never be added to consideration.
    //
    // Reducing the problem a little more, the minimum element of the window
    // must be greater than threshold/k
    //
    // HINT: "next and previous smallest element for every index"
    // next smallest element allows us to determine the size of the window
    // where the current element is relevant, since we only need consider the
    // smallest element of a window to determine if it crosses threshold/k.
    //
    // Not sure about previous smallest element, but the above seems like
    // a monotonic stack? More specifically, a monotonically non-decreasing
    // stack.
    //
    // {2, 3, 4}, see 3 < 4. Check stack. 2, 3, 4, where 2 is the min and will
    // not exceed the threshold. Remove. Does this mean a Deque is necessary.
    //
    // Hm. Doesnt seem like comparing the top of the stack is apt.
    // Checking with the min element, i.e. the front of the deque seems more
    // appropriate.
    //
    // {2, 3, 4, 3}, see 1 < 2. Check deque. threshold/k = 8/4 = 2
    // Pop front as once 1 is added, the current window's minimum will not
    // be relevant.
    // Okay. Instead of popping, I believe it should be an O(k) traversal to
    // check each window, {2, 3, 4, 3}, {3, 4, 3}, {4, 3}, {3}.
    //
    // Hm. Can we maintain the minimum of each window using a stack.
    // i.e. for {2, 3, 4, 3, 1}
    // minStack: {2, 2, 2, 2, 1}
    // Are there any actionable patterns here. i.e. since 1 < 2, we can start
    // checking the first 4 elements (by popping, since any subarray ending at
    // the smaller element '1' will implicitly include the first 4 elements.
    // NOT entirely correct! It will include previous numbers as long as there
    // are no smaller elements! e.g. {1, 2, 3, 2}, dont want to include 1.
    // Not viable. We cant update the minimum of {3, 4, 3} to 3 after popping 2.
    //
    // THOUGHT PROCESS OVER.
    // TAPPED OUT.
    // Reorder the equation nums[i] > threshold/k to k > threshold / nums[i],
    // which indicates the minimum size of the subarray that this element needs
    // to be considered valid.
    //
    // e.g. for {2, 3, 4, 3, 1}, threshold = 8.
    // minSizes: {4, 3, 3, 3, 9}
    // add {4, 1}
    // add {3, 1}
    // add {3, 1}
    // add {3, 1}, stack = {{4, 1}, {3, 1}, {3, 1}, {3, 1}}
    // pop {3, 1}, pop {3, 1}, pop {3, 1} => count = 3, greater than val 3.
    //
    // Therefore, popping and incrementing the counts indicate the number of
    // element to the RIGHT of the popped element that can be included, since
    // they are larger (or have a smaller minsize). Thus, if the accumulated
    // count is greater than the required size, we found an answer.

    // transform nums to represent the minimum size of the subarray necessary.
    // x > threshold / nums[i] => x >= threshold/nums[i] + 1
    // + 1 to deal with integer division AND strictly greater than condition.
    for (std::size_t i = 0; i < nums.size(); ++i) {
      nums[i] = threshold / nums[i] + 1;
    }

    // Monotonically non-increasing stack. An larger minSize indicates a
    // smaller element.
    // Stores {val, count}, where count indicates how many elements up till
    // the current element is in the subarray, i.e., greater than this element.
    std::stack<std::pair<int, std::size_t>> stk;

    // sentinel value to ensure any elements at the end of the iteration is
    // processed.
    nums.push_back(INT_MAX);

    for (std::size_t i = 0; i < nums.size(); ++i) {
      // 0 instead of 1, since we dont want to include the current element
      // yet.
      std::size_t count = 0;
      while (!stk.empty() && stk.top().first < nums[i]) {
        const auto [topSize, topCount] = stk.top();
        stk.pop();

        count += topCount;
        if (count >= topSize) {
          // there is indeed a subarray that fulfils the condition.
          return count;
        }
      }
      stk.emplace(nums[i], count + 1);
    }

    // if no valid subarrays
    return -1;
  }
};
