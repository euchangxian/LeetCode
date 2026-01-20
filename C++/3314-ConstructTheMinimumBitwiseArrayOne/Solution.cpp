#include <vector>

class Solution {
 public:
  std::vector<int> minBitwiseArray(std::vector<int>& nums) {
    // n prime integer.
    // Construct array ans of length n such that for each index i,
    // ans[i] | (ans[i] + 1) is equal to nums[i].
    // Minimise each value of ans[i] in the resulting array.
    // If not possible, ans[i] = -1.
    //
    // Given that primes are mostly odd (exception of 2), we have multiple
    // ways to construct x such that x | (x+1) = nums[i].
    // Consider the binary representation of nums[i].
    // 1. If nums[i] is 2, then impossible.
    // 2. If nums[i] is all 1s, i.e., 2^k - 1, then x = nums[i] >> 1.
    // 3. If the second last bit is set, then x = nums[i]-2
    // 4. Else, x = nums[i]-1
    //
    // Nope. There is a "core" pattern for the 3rd and 4th case.
    // If nums[i] has consecutive set '1' bits starting from the LSB, then
    // shift that consecutive subset right, retaining all the other bits.
    // We can obtain that tail using XOR:
    // x = (nums[i] XOR (nums[i]+1)) >> 1
    // In this case, we just shift right an additional time, to remove one more
    // bit from that tail, OR it with the remaining upper bits.
    // Case 2 can also be handled by this.
    const auto n = static_cast<int>(nums.size());
    std::vector<int> result;
    result.reserve(n);
    for (auto num : nums) {
      if (num == 2) {
        result.push_back(-1);
      } else {
        // auto tail = (num ^ (num + 1)) >> 1;
        // auto upper = num & ~tail;
        // result.push_back(upper | (tail >> 1));
        auto tail = (num + 1) & ~num;
        result.push_back(num ^ (tail >> 1));
      }
    }
    return result;
  }
};
