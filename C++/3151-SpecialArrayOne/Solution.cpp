#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  bool isArraySpecial(std::vector<int>& nums) {
    int prevParity = -1;
    for (int num : nums) {
      int parity = num & 1;
      if (parity == prevParity) {
        return false;
      }
      prevParity = parity;
    }
    return true;
  }
};
