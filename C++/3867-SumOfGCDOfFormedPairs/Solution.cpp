#include <algorithm>
#include <numeric>
#include <ranges>
#include <vector>

class Solution {
 public:
  long long gcdSum(std::vector<int>& nums) {
    // Construct array prefixGCD, where for each index i:
    // - mx_i         = max(nums[i], ...,nums[i])
    // - prefixGCD[i] = gcd(nums[i], mx_i)
    // Sort prefixGCD in non-decreasing order.
    // Pair the smallest unpaired, largest unpaired elements, until no more
    // pairs can be formed.
    // For each pair, gcd(smallest, largest).
    // Return the sum of the final GCD values.
    //
    // Seems like following instructions.
    const auto n = static_cast<int>(nums.size());

    auto prefixMax = 0;
    std::vector<int> prefixGCD;
    prefixGCD.reserve(n);
    for (auto x : nums) {
      prefixMax = std::max(prefixMax, x);
      prefixGCD.emplace_back(std::gcd(x, prefixMax));
    }

    std::ranges::sort(prefixGCD);

    auto sum = 0LL;
    auto paired = std::views::zip(prefixGCD, std::views::reverse(prefixGCD));
    for (auto [a, b] : paired | std::views::take(n / 2)) {
      sum += std::gcd(a, b);
    }
    return sum;
  }
};
