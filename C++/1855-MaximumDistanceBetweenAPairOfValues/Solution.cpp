#include <algorithm>
#include <vector>

class Solution {
 public:
  int maxDistance(std::vector<int>& nums1, std::vector<int>& nums2) {
    // Given non-increasing arrays.
    // (i, j) is valid if:
    // - i <= j and:
    // - nums1[i] <= nums2[j].
    // The distance of the pair is j-i.
    // Return the maximum distance of any valid pair, or 0.
    //
    // - Non-increasing, i<=j => two-pointers.
    // - Increment j while nums1[i] <= nums2[j], take the distance.
    const auto m = static_cast<int>(nums1.size());
    const auto n = static_cast<int>(nums2.size());

    auto result = 0;
    auto i = 0;
    auto j = 0;

    for (int i = 0; i < m && j < n; ++i) {
      while (j < n && nums1[i] <= nums2[j]) {
        ++j;
      }

      if (j <= n) {
        result = std::max(result, j - i - 1);
      }
    }

    return result;
  }
};
