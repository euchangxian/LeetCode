#include <algorithm>
#include <string>
#include <vector>

class Solution {
 public:
  std::string largestNumber(std::vector<int>& nums) {
    std::sort(nums.begin(), nums.end(), [](int a, int b) {
      std::string candidate1 = std::to_string(a) + std::to_string(b);
      std::string candidate2 = std::to_string(b) + std::to_string(a);

      // compare the concantenation of the two strings in lexicographical
      // order and return the larger one first.
      return candidate1 > candidate2;
    });

    // Check for edge case where the first number is 0
    if (nums[0] == 0) {
      return "0";
    }

    std::string result;
    result.reserve(1024);
    for (int num : nums) {
      result += std::to_string(num);
    }

    return result;
  }
};
