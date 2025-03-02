#include <cstddef>
#include <cstdlib>
#include <utility>
#include <vector>

class Solution {
 public:
  std::vector<std::vector<int>> mergeArrays(
      std::vector<std::vector<int>>& nums1,
      std::vector<std::vector<int>>& nums2) {
    // numsx[i] = [id, val] indicating number with id has value val.
    // Each array contains unique IDs, sorted in ascending order by ID.
    // Merge the two arrays such that:
    // - Each ID should be included only once, and its value should be the sum
    //   of values of the IDs in the two arrays (if it appears twice).
    // Two pointer for one-pass O(N).
    const int m = nums1.size();
    const int n = nums2.size();
    std::vector<std::vector<int>> result;
    result.reserve(m + n);

    int i = 0;
    int j = 0;
    while (i < m && j < n) {
      if (nums1[i][0] == nums2[j][0]) {
        nums1[i][1] += nums2[j][1];
        result.push_back(std::move(nums1[i]));
        ++i;
        ++j;
      } else if (nums1[i][0] < nums2[j][0]) {
        result.push_back(std::move(nums1[i]));
        ++i;
      } else {
        result.push_back(std::move(nums2[j]));
        ++j;
      }
    }

    while (i < m) {
      result.push_back(std::move(nums1[i++]));
    }

    while (j < n) {
      result.push_back(std::move(nums2[j++]));
    }
    return result;
  }
};
