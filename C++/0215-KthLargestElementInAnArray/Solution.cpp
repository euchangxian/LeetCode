#include <functional>
#include <queue>
#include <vector>

class Solution {
 public:
  int findKthLargest(std::vector<int>& nums, int k) {
    // Maintain the k largest elements of nums.
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;

    for (int num : nums) {
      minHeap.push(num);

      if (minHeap.size() > k) {
        minHeap.pop();
      }
    }
    return minHeap.top();
  }
};
