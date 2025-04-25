#include <algorithm>
#include <vector>

class Solution {
 public:
  std::vector<std::vector<int>> subsetsWithDup(std::vector<int>& nums) {
    const int n = nums.size();

    // we want to handle duplicate subsets.
    // At each element, the choices are to:
    // 1. skip current, and duplicates
    // 2. append to existing list
    std::ranges::sort(nums);
    std::vector<std::vector<int>> subsets;
    subsets.reserve(1 << n);
    std::vector<int> subset;
    subset.reserve(n);
    dfs(nums, subsets, subset, 0);
    return subsets;
  }

 private:
  void dfs(std::vector<int>& nums,
           std::vector<std::vector<int>>& subsets,
           std::vector<int>& subset,
           int idx) {
    subsets.push_back(subset);

    for (int i = idx; i < nums.size(); ++i) {
      if (i > idx && nums[i] == nums[i - 1]) {
        // for the current recursive call, skip adding duplicates
        continue;
      }
      subset.push_back(nums[i]);
      dfs(nums, subsets, subset, i + 1);
      subset.pop_back();
    }
  }
};
