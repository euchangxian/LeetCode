#include <cstdlib>
#include <vector>

class Solution {
 public:
  int beautifulSubsets(std::vector<int>& nums, int k) {
    int beautifulSubsets = getBeautifulSubsets(nums, k);
    return beautifulSubsets;
  }

 private:
  int getBeautifulSubsets(const std::vector<int>& nums, int k) {
    std::vector<std::vector<int>> subsets;
    std::vector<int> currSet;
    int count = 0;
    getSubsets(nums, k, subsets, currSet, 0, count);
    return count - 1;  // empty set
  }

  void getSubsets(const std::vector<int>& nums,
                  int k,
                  std::vector<std::vector<int>>& subsets,
                  std::vector<int>& currSet,
                  int start,
                  int& count) {
    if (start >= nums.size()) {
      count++;
      return;
    }

    getSubsets(nums, k, subsets, currSet, start + 1, count);
    if (currSet.empty() || isBeautiful(currSet, nums[start], k)) {
      currSet.push_back(nums[start]);
      getSubsets(nums, k, subsets, currSet, start + 1, count);
      currSet.pop_back();
    }
  }

  bool isBeautiful(const std::vector<int>& subset, int toAdd, int k) {
    for (int num : subset) {
      if (std::abs(num - toAdd) == k) {
        return false;
      }
    }
    return true;
  }
};
