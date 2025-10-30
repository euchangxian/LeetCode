#include <algorithm>
#include <numeric>
#include <vector>

class Solution {
 public:
  int validSubarraySplit(std::vector<int>& nums) {
    // Splitting nums into subarrays is valid if:
    // - The GCD of the first and last element is greater than 1,
    // - each element of nums belong to exactly one subarray
    // Return the minimum number of subarrays in a valid split. Otherwise -1.
    //
    // GCD(x, y) > 1 => not coprime.
    // GCD(x, x) == x. Therefore a subarray of size 1 is valid.
    //
    // Check first and last? If not valid, then a split is needed.
    // Seems like we can either shift left or right pointers.
    // How can we model this then? What about in terms of placing a "partition".
    constexpr int INF = 1E9;
    const auto n = static_cast<int>(nums.size());
    std::vector<int> dp(n + 1, INF);
    dp[0] = 0;

    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= i; ++j) {
        if (std::gcd(nums[j - 1], nums[i - 1]) > 1) {
          dp[i] = std::min(dp[i], dp[j - 1] + 1);
        }
      }
    }

    return dp[n] == INF ? -1 : dp[n];
  }
};
