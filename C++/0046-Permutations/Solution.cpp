#include <utility>
#include <vector>

using namespace std;
class Solution {
private:
  void generatePermutations(vector<int> &nums,
                            vector<vector<int>> &permutations, int index) {
    if (index >= nums.size()) {
      permutations.push_back(nums);
      return;
    }

    for (int i = index; i < nums.size(); ++i) {
      swap(nums[index], nums[i]);
      generatePermutations(nums, permutations, index + 1);
      swap(nums[index], nums[i]);
    }
    return;
  }

public:
  vector<vector<int>> permute(vector<int> &nums) {
    vector<vector<int>> permutations;
    generatePermutations(nums, permutations, 0);
    return permutations;
  }
};
