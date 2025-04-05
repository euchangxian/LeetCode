#include <functional>
#include <numeric>
#include <vector>

class Solution {
 public:
  int subsetXORSum(std::vector<int>& nums) {
    // Notice that of the 2^n subsets, nums[i] will be in exactly half of them.
    // Let k=2^n.
    // Then, the bits of nums[i] will be included k/2 times.
    // Not exactly correct to say this. The bits may be XOR-ed/toggled off/on.
    // Hm. If the x-th bit is set in nums[i], it must be set in half of the
    // XOR totals.
    // If the x-th bit is set in more than one of the elements, it will be set
    // in half of the XOR totals. More specifically, consider the previous
    // scenario where half of the subsets have the xth bit set, and the other
    // half do not.
    // Then, the on-subset will be toggled to off, and vice-versa, remaining
    // at half.
    // Thus, we can take the bitwise OR of every element to get all x_i bits,
    // then add them to the sum k/2 = 2^(n-1) = (1 << (n-1)) times.
    // Wild.
    const int n = nums.size();
    return std::reduce(nums.begin(), nums.end(), 0, std::bit_or<>{}) << (n - 1);
  }

  // Lol. This is worse than expected.
  // Simply dfs(nums, i, total) is sufficient.
  int subsetXORSumBacktracking(std::vector<int>& nums) {
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
