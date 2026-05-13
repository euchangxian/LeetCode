#include <algorithm>
#include <array>
#include <ranges>
#include <span>
#include <vector>

class Solution {
 public:
  int minMoves(std::vector<int>& nums, int limit) {
    // Even length nums array.
    // Replace any integer from nums with another integer between [1..limit].
    // nums is complementary if for all indices i, nums[i]+nums[n-1-i] is equal
    // to the same number.
    // Return the minimum number of moves required to make nums complementary.
    //
    // Count occurences of sums.
    // Then, each pair != sum will require at most 2 operations if they are
    // greater than the target sum.
    //
    // Naive greedy does not work. If min({nums[i], nums[n-1-i]}) is greater
    // than the target sum, then two operations are needed.
    // The second case is when max({nums[i], nums[n-1-i]}) + limit is smaller
    // than the target sum.
    // Otherwise, only 0/1 operations is needed.
    //
    // From these cases, we can compute intervals where we need 0/1/2
    // operations. Let x be the min, y be the max.
    // Then, in increasing value of target between [2..y+limit+1]
    // - 2   <= target < x+1         => 2 operations: reduce x and y.
    // - x+1 <= target < x+y         => 1 operation : reduce y = target-x
    // - x+y == target               => 0 operations
    // - x+y < target <= y+limit    => 1 operation : increase x = target-y
    // - y+limit < target <= 2*limit => 2 operations: increase x and y
    constexpr int MAX_VAL = 1E5;
    const auto n = static_cast<int>(nums.size());
    std::array<int, 2 * MAX_VAL + 1> diff{};

    for (const auto [a, b] : std::views::zip(nums, nums | std::views::reverse) |
                                 std::views::take(n / 2)) {
      auto x = std::min(a, b);
      auto y = std::max(a, b);

      diff[2] += 2;
      --diff[x + 1];
      --diff[x + y];
      ++diff[x + y + 1];
      ++diff[y + limit + 1];
    }

    int result = n;
    int prefix = 0;
    for (auto f : std::span{diff.begin() + 2, diff.begin() + 2 * limit + 1}) {
      prefix += f;
      result = std::min(result, prefix);
    }
    return result;
  }
};
