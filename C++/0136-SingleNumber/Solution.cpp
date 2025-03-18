#include <vector>

class Solution {
 public:
  int singleNumber(std::vector<int>& nums) {
    int single = 0;
    for (auto num : nums) {
      single ^= num;
    }
    return single;
  }
};
