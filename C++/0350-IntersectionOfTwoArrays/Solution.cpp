#include <unordered_map>
#include <vector>

class Solution {
 public:
  std::vector<int> intersect(std::vector<int>& nums1, std::vector<int>& nums2) {
    if (nums2.size() < nums1.size()) {
      return intersect(nums2, nums1);
    }

    std::unordered_map<int, int> frequencies;
    for (int num : nums1) {
      ++frequencies[num];
    }

    std::vector<int> result;
    for (int num : nums2) {
      if (--frequencies[num] >= 0) {
        result.push_back(num);
      }
    }
    return result;
  }
};
