#include <algorithm>
#include <vector>

class Solution {
 public:
  int maximumElementAfterDecrementingAndRearranging(std::vector<int>& arr) {
    // Perform some operations (or None) on arr such that:
    // - the first element is 1
    // - the absolute difference between any 2 adjacent elements <= 1
    // Two types of operations:
    // 1. Decrease the value of any element to a smaller positive integer
    // 2. Rearrange arr in any order.
    //
    // Sort.
    // Find violations, since first element must be 1.
    std::ranges::sort(arr);
    const auto n = static_cast<int>(arr.size());
    auto result = 1;
    for (auto i = 1; i < n; ++i) {
      if (arr[i] >= result + 1) {
        ++result;
      }
    }
    return result;
  }
};
