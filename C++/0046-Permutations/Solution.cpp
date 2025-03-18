#include <utility>
#include <vector>

class Solution {
 private:
  void generatePermutations(std::vector<int>& nums,
                            std::vector<std::vector<int>>& permutations,
                            int index) {
    if (index >= nums.size()) {
      permutations.push_back(nums);
      return;
    }

    for (int i = index; i < nums.size(); ++i) {
      std::swap(nums[index], nums[i]);
      generatePermutations(nums, permutations, index + 1);
      std::swap(nums[index], nums[i]);
    }
    return;
  }

 public:
  std::vector<std::vector<int>> permute(std::vector<int>& nums) {
    std::vector<std::vector<int>> permutations;
    generatePermutations(nums, permutations, 0);
    return permutations;
  }
};
