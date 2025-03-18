#include <algorithm>
#include <cstddef>
#include <vector>

class Solution {
 public:
  int maximumScore(std::vector<int>& nums, std::vector<int>& multipliers) {
    // Notice that we do not actually need 3 states i.e., O(m^3). We can deduce
    // the number of right elements taken, i.e., the rightIdx from just the
    // leftIdx.
    // Thereby reducing to O(m^2) space.
    const std::size_t n = nums.size();
    const std::size_t m = multipliers.size();

    std::vector<std::vector<int>> memo(m, std::vector<int>(m, 0));
    return dfs(nums, multipliers, memo, 0, 0);
  }

 private:
  int dfs(const std::vector<int>& nums,
          const std::vector<int>& multipliers,
          std::vector<std::vector<int>>& memo,
          int leftTaken,
          int multIdx) {
    if (multIdx >= multipliers.size()) {
      return 0;
    }

    if (memo[leftTaken][multIdx]) {
      return memo[leftTaken][multIdx];
    }

    int takeLeft = multipliers[multIdx] * nums[leftTaken] +
                   dfs(nums, multipliers, memo, leftTaken + 1, multIdx + 1);

    // multipliersIdx - leftTaken indicate the current number of rightTaken
    // Then do nums.size - 1 - rightTaken to get the idx.
    int rightIdx = (static_cast<int>(nums.size()) - 1) - (multIdx - leftTaken);
    int takeRight = multipliers[multIdx] * nums[rightIdx] +
                    dfs(nums, multipliers, memo, leftTaken, multIdx + 1);

    memo[leftTaken][multIdx] = std::max(takeLeft, takeRight);
    return memo[leftTaken][multIdx];
  }
};
