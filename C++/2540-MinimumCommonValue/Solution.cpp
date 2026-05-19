#include <vector>

class Solution {
 public:
  int getCommon(std::vector<int>& nums1, std::vector<int>& nums2) {
    // nums1 and nums2 in sorted non-decreasing order.
    // Return the minimum integer common to both arrays.
    // Else return -1.
    const auto m = static_cast<int>(nums1.size());
    const auto n = static_cast<int>(nums2.size());
    for (auto i = 0, j = 0; i < m && j < n;) {
      if (nums1[i] == nums2[j]) {
        return nums1[i];
      }
      if (nums1[i] < nums2[j]) {
        ++i;
      } else {
        ++j;
      }
    }

    return -1;
  }
};
