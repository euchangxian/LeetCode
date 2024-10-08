#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int beautifulSubsets(vector<int>& nums, int k) {
    int beautifulSubsets = getBeautifulSubsets(nums, k);
    return beautifulSubsets;
  }

 private:
  int getBeautifulSubsets(vector<int> const& nums, int k) {
    vector<vector<int>> subsets;
    vector<int> currSet;
    int count = 0;
    getSubsets(nums, k, subsets, currSet, 0, count);
    return count - 1;  // empty set
  }

  void getSubsets(vector<int> const& nums,
                  int k,
                  vector<vector<int>>& subsets,
                  vector<int>& currSet,
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

  bool isBeautiful(vector<int> const& subset, int toAdd, int k) {
    for (int num : subset) {
      if (abs(num - toAdd) == k) {
        return false;
      }
    }
    return true;
  }
};

int main() {
  vector<int> nums = {10, 4, 5, 7, 2, 1};
  int k = 3;
  cout << Solution().beautifulSubsets(nums, k) << endl;
}
