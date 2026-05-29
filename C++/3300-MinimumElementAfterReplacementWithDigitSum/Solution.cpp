#include <algorithm>
#include <ranges>
#include <vector>

class Solution {
 public:
  int minElement(std::vector<int>& nums) {
    // replace each element in nums with the sum of its digits.
    // Return the minimum element after replacement.
    constexpr auto digitSum = [](auto x) {
      auto sum = 0;
      while (x) {
        sum += x % 10;
        x /= 10;
      }
      return sum;
    };

    return std::ranges::min(nums | std::views::transform(digitSum));
  }
};
