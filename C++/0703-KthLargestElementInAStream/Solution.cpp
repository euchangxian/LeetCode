#include <functional>
#include <queue>
#include <vector>

class KthLargest {
  // Create a min-heap where the kth largest element is at the top,
  // subsequent elements are all larger.
  // To visualise, consider a sorted array in ascending order. We only want
  // the kth element from the back. Adding a smaller element to the array
  // than the kth element will not affect the position of the kth largest
  // element
  std::priority_queue<int, std::vector<int>, std::greater<int>> stream;
  int k;

 public:
  KthLargest(int k, std::vector<int>& nums) : k(k) {
    for (int num : nums) {
      stream.push(num);
      if (stream.size() > k) {
        stream.pop();
      }
    }
  }

  int add(int val) {
    // Constraints guarantee there will be at least k elements in the array
    if (stream.size() < k || stream.top() < val) {
      stream.push(val);
    }
    while (stream.size() > k) {
      stream.pop();
    }
    return stream.top();
  }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */
