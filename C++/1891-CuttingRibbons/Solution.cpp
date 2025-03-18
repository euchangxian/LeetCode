#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  int maxLength(std::vector<int>& ribbons, int k) {
    // binary search probably, where we want to seach for maxLength.
    int left = 0;
    int right = *std::max_element(ribbons.begin(), ribbons.end());

    while (left < right) {
      int mid = left + (right - left + 1) / 2;

      if (feasible(ribbons, k, mid)) {
        // try a bigger cut
        left = mid;
      } else {
        right = mid - 1;
      }
    }
    return left;
  }

 private:
  bool feasible(std::vector<int>& ribbons, int k, int len) {
    for (int ribbon : ribbons) {
      k -= (ribbon / len);
    }
    return k <= 0;
  }
};
