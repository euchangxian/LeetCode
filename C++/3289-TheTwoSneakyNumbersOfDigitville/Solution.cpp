#include <vector>

class Solution {
 public:
  std::vector<int> getSneakyNumbers(std::vector<int>& nums) {
    // list of nums that is supposed to contain [0..n-1] exactly once.
    // Two numbers occur twice, making the list longer.
    // Return the two numbers.
    //
    // Can we do O(1) space?
    // This is same as 260-SingleNumberIII
    // XOR. Partition into two groups.
    const auto n = static_cast<int>(nums.size()) - 2;

    std::vector<int> result(2, 0);
    int xorSum = nums[n] ^ nums[n + 1];
    for (int i = 0; i < n; ++i) {
      xorSum ^= i ^ nums[i];
    }

    auto lsb = xorSum & -xorSum;
    for (int i = 0; i < n; ++i) {
      result[static_cast<bool>(nums[i] & lsb)] ^= nums[i];
      result[static_cast<bool>(i & lsb)] ^= i;
    }

    result[static_cast<bool>(nums[n] & lsb)] ^= nums[n];
    result[static_cast<bool>(nums[n + 1] & lsb)] ^= nums[n + 1];

    return result;
  }
};
