#include <vector>

class Solution {
 public:
  bool threeConsecutiveOdds(std::vector<int>& arr) {
    int consecutiveOdds = 0;
    for (int num : arr) {
      if (num & 1) {
        if (++consecutiveOdds >= 3) {
          return true;
        }
      } else {
        consecutiveOdds = 0;
      }
    }
    return false;
  }
};
