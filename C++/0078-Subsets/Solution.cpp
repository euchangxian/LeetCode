#include <vector>

class Solution {
 public:
  std::vector<std::vector<int>> subsets(std::vector<int>& nums) {
    std::vector<std::vector<int>> subsets;
    std::vector<int> currSet;
    generateSubsets(nums, subsets, currSet, 0);
    return subsets;
  }

 private:
  void generateSubsets(const std::vector<int>& nums,
                       std::vector<std::vector<int>>& subsets,
                       std::vector<int>& currSet,
                       int idx) {
    if (idx >= nums.size()) {
      subsets.push_back(currSet);
      return;
    }
    generateSubsets(nums, subsets, currSet, idx + 1);
    currSet.push_back(nums[idx]);
    generateSubsets(nums, subsets, currSet, idx + 1);
    currSet.pop_back();
    return;
  }
};
