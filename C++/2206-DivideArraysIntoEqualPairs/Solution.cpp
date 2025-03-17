#include <bitset>
#include <vector>

class Solution {
 public:
  bool divideArray(std::vector<int>& nums) {
    // 2*n integers, n pairs.
    std::bitset<501> frequency{};
    for (int num : nums) {
      frequency[num].flip();
    }
    return frequency.count() == 0;
  }
};
