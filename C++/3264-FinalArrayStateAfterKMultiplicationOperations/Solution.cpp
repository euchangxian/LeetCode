#include <cstddef>
#include <cstdlib>
#include <functional>
#include <queue>
#include <utility>
#include <vector>

class Solution {
 public:
  std::vector<int> getFinalState(std::vector<int>& nums,
                                 int k,
                                 int multiplier) {
    // minHeap would be straightforward: O(n) heapify, O(k * logn) operations.
    // O(n) space is necessary though, since we want to maintain the original,
    // relative positions after multiplications.
    // {val, idx}
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        std::greater<>>
        minHeap;
    for (int i = 0; i < nums.size(); ++i) {
      minHeap.emplace(nums[i], i);
    }

    while (k--) {
      auto [val, idx] = minHeap.top();
      minHeap.pop();

      minHeap.emplace(val * multiplier, idx);
      nums[idx] = val * multiplier;
    }

    return nums;
  }
};
