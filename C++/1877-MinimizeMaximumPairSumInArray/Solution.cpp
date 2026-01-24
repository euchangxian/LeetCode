#include <algorithm>
#include <ranges>
#include <tuple>
#include <vector>

class Solution {
 public:
  int minPairSum(std::vector<int>& nums) {
    // pair sum of (a, b) = a+b.
    // Maximum pair sum is the largest pair sum in a list of pairs.
    // Pair up the elements of nums into n/2 pairs such that:
    // - maximum pair sum is minimized.
    //
    // Can we greedily pair min+max element at each iteration?
    // Seems like it.
    // Consider: [1, 8, 9, 10]
    // The largest element paired with any of the non-smallest element will
    // result in a larger maximum pair sum.
    const auto n = static_cast<int>(nums.size());
    std::ranges::sort(nums);
    auto maxView = nums | std::views::reverse;
    auto pair = std::views::zip(nums, maxView) | std::views::take(n / 2);
    auto pairSum =
        pair | std::views::transform([](const auto& p) {
          return std::apply([](auto... args) { return (args + ...); }, p);
        });
    return std::ranges::max(pairSum);
  }
};
