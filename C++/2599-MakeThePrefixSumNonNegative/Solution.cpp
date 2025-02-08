#include <cstddef>
#include <cstdlib>
#include <queue>
#include <vector>

class Solution {
 public:
  int makePrefSumNonNegative(std::vector<int>& nums) {
    // Any number of times:
    // - pick any element from nums and put it at the back.
    //
    // Return the minimum number of operations such that the prefix sum does
    // not contain negative integers.
    // Input is such that it is always possible.
    // Given that the input is always valid, a naive, but non-optimal/WA method
    // would be to partition the negative numbers such that they are all at
    // the back.
    // Greedy?
    // Maintain a running prefix sum such that if the prefix sum ever goes
    // below negative, then insert the element at the back.
    // Ah, for a sequence of negative numbers that may cause the prefix to go
    // negative, we want to remove the most negative ones, to minimize removals.

    // maxHeap, since we want most negative at the top, we negate.
    std::priority_queue<int> negatives;

    long long prefix = 0;
    int ops = 0;
    for (int num : nums) {
      if (num < 0) {
        negatives.push(-num);
      }

      prefix += num;

      while (prefix < 0) {
        prefix += negatives.top();
        negatives.pop();

        ++ops;
      }
    }
    return ops;
  }
};
