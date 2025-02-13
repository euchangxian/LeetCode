#include <algorithm>
#include <cstddef>
#include <functional>
#include <vector>

using i64 = long long;
class Solution {
 public:
  int minOperations(std::vector<int>& nums, int k) {
    // Problem constraints guarantee that an answer always exists. No need for
    // input validation.
    //
    // Use a minHeap to extract the two smallest integer x, y in nums
    // efficiently.
    // Repeat until x, y is greater than k, as both x, y are the 2 smallest
    // elements.
    const std::size_t n = nums.size();
    std::vector<i64> llNums(n);
    for (std::size_t i = 0; i < n; ++i) {
      llNums[i] = static_cast<i64>(nums[i]);
    }

    // Use a minHeap.
    const auto cmp = std::greater<>{};
    std::make_heap(llNums.begin(), llNums.end(), cmp);

    int operations = 0;
    while (llNums.size() >= 2) {
      const i64 x = llNums.front();
      std::pop_heap(llNums.begin(), llNums.end(), cmp);
      llNums.pop_back();  // actually pop from the underlying array

      const i64 y = llNums.front();
      std::pop_heap(llNums.begin(), llNums.end(), cmp);

      if (x >= k && y >= k) {
        break;
      }

      const i64 toAdd = std::min(x, y) * 2 + std::max(x, y);

      llNums.back() = toAdd;
      std::push_heap(llNums.begin(), llNums.end(), cmp);

      ++operations;
    }
    return operations;
  }
};
