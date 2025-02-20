#include <cstddef>
#include <cstdlib>
#include <string>
#include <vector>

class Solution {
 public:
  std::string findDifferentBinaryString(std::vector<std::string>& nums) {
    const int n = nums.size();
    std::string result;
    result.reserve(16);
    for (int i = 0; i < n; ++i) {
      // if nums[i][i] == 0, pick 1
      // else pick 0
      // Cantor's Diagonalization
      result += ('1' - nums[i][i]) + '0';
    }
    return result;
  }
};
