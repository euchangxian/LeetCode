#include <array>
#include <cstddef>
#include <cstdlib>
#include <ranges>
#include <vector>

constexpr auto digitSum = [](int x) -> int {
  int sum = 0;
  while (x) {
    sum += x % 10;
    x /= 10;
  }
  return sum;
};

class Solution {
 public:
  int maximumSum(std::vector<int>& nums) {
    // Let S(x) be the sum of the digits in x.
    // Array of positive integers. Choose i != j such that
    // S(nums[i]) = S(nums[j]).
    // Want max value.
    // Essentially two-sum like LOL.

    // nums[i] <= 10e9 => sum of digits is at most 9 * 9.
    std::array<int, 100> seen{};
    auto sumView = nums | std::ranges::views::transform(digitSum);

    int maxSum = -1;
    for (auto [num, sum] : std::ranges::views::zip(nums, sumView)) {
      if (seen[sum]) {
        maxSum = std::max(maxSum, seen[sum] + num);
      }
      seen[sum] = std::max(seen[sum], num);
    }
    return maxSum;
  }
};
