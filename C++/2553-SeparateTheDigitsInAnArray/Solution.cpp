#include <ranges>
#include <vector>

class Solution {
 public:
  std::vector<int> separateDigits(std::vector<int>& nums) {
    // Return an array answer that consists of the digits of each integer in
    // nums after separating them in the same order they appear in nums.
    // E.g., for the integer 10921, the separatino of its digits is [1,0,9,2,1].
    constexpr auto separate = [](auto num) {
      std::vector<int> buffer;
      buffer.reserve(5);

      while (num) {
        buffer.emplace_back(num % 10);
        num /= 10;
      }
      return buffer;
    };
    const auto n = static_cast<int>(nums.size());
    std::vector<int> answer;
    answer.reserve(n * 5);  // nums[i] <= 1E5
    for (auto num : nums) {
      for (auto x : separate(num) | std::views::reverse) {
        answer.emplace_back(x);
      }
    }
    return answer;
  }
};
