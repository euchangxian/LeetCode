#include <vector>

using namespace std;
class Solution {
public:
  vector<vector<int>> subsets(vector<int> &nums) {
    vector<vector<int>> subsets;
    vector<int> currSet;
    generateSubsets(nums, subsets, currSet, 0);
    return subsets;
  }

private:
  void generateSubsets(vector<int> const &nums, vector<vector<int>> &subsets,
                       vector<int> &currSet, int idx) {
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
