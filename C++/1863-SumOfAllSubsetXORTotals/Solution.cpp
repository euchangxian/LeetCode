#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<int>> generateAllSubsets(vector<int> const& nums) {
    vector<vector<int>> subsets;
    vector<int> currSet;
    generateSubsets(nums, subsets, currSet, 0);
    return subsets;
  }

  int subsetXORSum(vector<int>& nums) {
    vector<vector<int>> subsets = generateAllSubsets(nums);
    int xorSum = 0;

    for (auto subset : subsets) {
      int subsetSum = 0;
      for (int i : subset) {
        subsetSum ^= i;
      }
      xorSum += subsetSum;
    }
    return xorSum;
  }

 private:
  void generateSubsets(vector<int> const& nums,
                       vector<vector<int>>& subsets,
                       vector<int>& currSet,
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

int main() {
  Solution soln = Solution();
  vector<vector<int>> subsets = soln.generateAllSubsets({1, 2, 3});
  for (auto subset : subsets) {
    cout << "{";
    for (auto i : subset) {
      cout << i << " ";
    }
    cout << "}" << endl;
  }
}
