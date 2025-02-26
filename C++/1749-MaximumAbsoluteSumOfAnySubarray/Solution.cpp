#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  int maxAbsoluteSum(std::vector<int>& nums) {
    // kadanes?? absolute sum?
    // why would the output be possibly empty?
    // oh!!
    // its not abs each number and consider them. Its to abs the end result.
    // Therefore, kadanes twice? One for most negative, one for most positive.
    int posSum = -10e4;
    int negSum = 10e4;
    int best = 0;
    for (int num : nums) {
      posSum = std::max(num, posSum + num);
      negSum = std::min(num, negSum + num);
      best = std::max({best, posSum, -negSum});
    }

    return best;
  }
};
