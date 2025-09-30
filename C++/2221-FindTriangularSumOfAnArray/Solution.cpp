#include <array>
#include <numeric>
#include <vector>

constexpr int MAX_N = 1000;
constexpr int MOD = 10;

auto PASCAL_TABLE = []() {
  std::array<std::array<int, MAX_N + 1>, MAX_N + 1> dp{};
  for (int i = 0; i <= MAX_N; ++i) {
    dp[i][0] = 1;
    for (int j = 1; j <= i; ++j) {
      dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % MOD;
    }
  }
  return dp;
}();

class Solution {
 public:
  int triangularSum(std::vector<int>& nums) {
    return std::inner_product(nums.begin(), nums.end(),
                              PASCAL_TABLE[nums.size() - 1].begin(), 0) %
           10;
  }

  int triangularSumSimulation(std::vector<int>& nums) {
    // Given nums[i] = [0..9]
    // The triangular sum of nums is the value of the remaining element in nums
    // after the process terminates:
    // 1. If n == 1, terminate. Else, create newNums of length n-1.
    // 2. For each index i, 0 <= i < n-1 (i.e., for each element in newNums):
    //    newNums[i] = (nums[i] + nums[i+1]) % 10
    // 3. Replace nums with newNums, repeat.
    //
    // Can we do better than simulation? ModSum?
    // Consider the final sum without modulo:
    // - Going from one level to the next, each internal element of nums,
    //   i.e., index 0 < i < n-1 is included in the sum twice.
    // Can we derive the number of times an element is included in the final
    // sum?
    // Yeah. Nth row of the Pascal's Triangle is the frequency of occurence in
    // the final sum.
    auto n = static_cast<int>(nums.size());
    while (n != 1) {
      for (int i = 0; i < n - 1; ++i) {
        nums[i] = (nums[i] + nums[i + 1]) % 10;
      }
      --n;
    }
    return nums[0];
  }
};
