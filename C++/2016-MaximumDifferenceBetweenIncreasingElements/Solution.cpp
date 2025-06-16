#include <algorithm>
#include <vector>

class Solution {
 public:
  int maximumDifference(std::vector<int>& nums) {
    // just maintain prefix minimum...
    const int n = nums.size();
    int result = -1;
    int pmin = nums.front();
    for (int j = 1; j < n; ++j) {
      if (nums[j] > pmin) {
        result = std::max(result, nums[j] - pmin);
      } else {
        pmin = std::min(pmin, nums[j]);
      }
    }
    return result;
  }

  int maximumDifferenceNaive(std::vector<int>& nums) {
    // Find the maximum difference between nums[i] and nums[j] such that
    // 0 <= i < j < n and nums[i] < nums[j]
    // i.e., a larger element to the right.
    // O(N^2) is trivial.
    // Felt like Buy and Sell Stock. Lol.
    // Seems like monotonic. Do we need the stack?
    const int n = nums.size();
    int result = -1;
    std::vector<int> stk;
    for (int i = 0; i < nums.size(); ++i) {
      while (!stk.empty() && nums[i] <= stk.back()) {
        stk.pop_back();
      }
      stk.push_back(nums[i]);
      if (stk.size() > 1) {
        result = std::max(result, stk.back() - stk.front());
      }
    }
    return result;
  }
};
