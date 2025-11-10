#include <stack>
#include <vector>

class Solution {
 public:
  int minOperations(std::vector<int>& nums) {
    // given n non-negative integers.
    // Apply any number of operations such that all elements become 0.
    // In one operation:
    // - Select a subarray [i,j] such that 0 <= i <= j < n and set all
    //   occurences of the MINIMUM non-negative integer in that subarray to 0.
    // Return the minimum number of operations.
    //
    // Maximum operations required is n: subarrays of size 1.
    // Visualising, it seems that if we select the whole subarray, we
    // effectively create partitions such that we need to operate on both sides.
    // e.g., [3, 2, 1, 2, 3] => [3, 2, 0, 2, 3]
    // If there are any 0s in the selected subarray, the operation will be
    // "useless".
    //
    // Hm. i.e., if there are any smaller numbers between identical numbers x,
    // then these identical numbers cannot be set to 0 in the same operation.
    //
    // Monotonic Non-Decreasing Stack?
    // on the next element,
    // - If greater or equal, push to stack
    // - otherwise, each distinct element from the top of the stack require a
    //   separate operation.
    const auto n = static_cast<int>(nums.size());
    std::stack<int> stk;
    stk.push(0);

    int result = 0;
    for (int x : nums) {
      while (!stk.empty() && x < stk.top()) {
        stk.pop();
      }

      // not equal, extra operation needed
      if (stk.empty() || x > stk.top()) {
        ++result;
        stk.push(x);
      }
    }
    return result;
  }
};
