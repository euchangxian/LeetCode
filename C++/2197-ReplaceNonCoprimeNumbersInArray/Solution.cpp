#include <numeric>
#include <vector>

class Solution {
 public:
  std::vector<int> replaceNonCoprimes(std::vector<int>& nums) {
    // Given nums, perform the steps:
    // 1. Find any two adjacent numbers in nums that are coprime.
    // 2. If no such numbers are found, stop.
    // 3. Otherwise, delete the two numbers, replace with their LCM.
    // 4. Repeat.
    // Return the final modified array.
    // It can be shown that replacing adjacent non-coprime numbers in any
    // arbitrary order will lead to the same result.
    //
    // This means we can run a stack, and iteratively compare the current
    // element with the top of the stack.
    std::vector<int> result;
    result.reserve(nums.size());
    for (auto num : nums) {
      while (!result.empty() && std::gcd(num, result.back()) > 1) {
        num = std::lcm(result.back(), num);
        result.pop_back();
      }
      result.emplace_back(num);
    }
    return result;
  }
};
