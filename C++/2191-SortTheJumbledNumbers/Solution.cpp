#include <algorithm>
#include <unordered_map>
#include <vector>

class Solution {
 public:
  std::vector<int> sortJumbled(std::vector<int>& mapping,
                               std::vector<int>& nums) {
    std::unordered_map<int, int> mappedNumbers;
    for (int i = 0; i < nums.size(); ++i) {
      int mapped = 0;
      int exp = 0;

      int num = nums[i];
      if (num == 0) {
        // Handle edge case
        mappedNumbers[0] = mapping[0];
        continue;
      }
      while (num > 0) {
        int digit = num % 10;
        mapped += mapping[digit] * pow(10, exp++);

        num /= 10;
      }
      mappedNumbers[nums[i]] = mapped;
    }

    std::stable_sort(nums.begin(), nums.end(),
                     [&mappedNumbers](int num1, int num2) {
                       return mappedNumbers[num1] < mappedNumbers[num2];
                     });
    return nums;
  }
};
