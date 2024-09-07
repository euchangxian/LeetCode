#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class Solution {
public:
  int findKthLargest(vector<int> &nums, int k) {
    // Maintain the k largest elements of nums.
    priority_queue<int, vector<int>, greater<int>> minHeap;

    for (auto const &num : nums) {
      minHeap.push(num);

      if (minHeap.size() > k) {
        minHeap.pop();
      }
    }
    return minHeap.top();
  }
};
