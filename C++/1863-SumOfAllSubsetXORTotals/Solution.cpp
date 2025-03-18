#include <vector>

class Solution {
 public:
  int subsetXORSum(std::vector<int>& nums) {
    std::vector<std::vector<int>> subsets = generateAllSubsets(nums);
    int xorSum = 0;

    for (const auto& subset : subsets) {
      int subsetSum = 0;
      for (int i : subset) {
        subsetSum ^= i;
      }
      xorSum += subsetSum;
    }
    return xorSum;
  }

 private:
  std::vector<std::vector<int>> generateAllSubsets(
      const std::vector<int>& nums) {
    std::vector<std::vector<int>> subsets;
    std::vector<int> currSet;
    generateSubsets(nums, subsets, currSet, 0);
    return subsets;
  }

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
