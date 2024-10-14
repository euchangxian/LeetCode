#include <algorithm>
#include <cstddef>
#include <functional>
#include <vector>

using namespace std;
class Solution {
 public:
  int minOperations(vector<int>& nums, int k) {
    // Problem constraints guarantee that an answer always exists. No need for
    // input validation.
    //
    // Use a minHeap to extract the two smallest integer x, y in nums
    // efficiently.
    // Repeat until x, y is greater than k, as both x, y are the 2 smallest
    // elements.
    const size_t n = nums.size();
    vector<long long> llNums(n);
    for (size_t i = 0; i < n; ++i) {
      llNums[i] = static_cast<long long>(nums[i]);
    }

    // Use a minHeap.
    const auto cmp = greater<>{};
    std::make_heap(llNums.begin(), llNums.end(), cmp);

    int operations = 0;
    while (llNums.size() >= 2) {
      const long long x = llNums.front();
      std::pop_heap(llNums.begin(), llNums.end(), cmp);
      llNums.pop_back();  // actually pop from the underlying array

      const long long y = llNums.front();
      std::pop_heap(llNums.begin(), llNums.end(), cmp);

      if (x >= k && y >= k) {
        break;
      }

      const long long toAdd = std::min(x, y) * 2 + std::max(x, y);

      llNums.back() = toAdd;
      std::push_heap(llNums.begin(), llNums.end(), cmp);

      ++operations;
    }
    return operations;
  }
};
