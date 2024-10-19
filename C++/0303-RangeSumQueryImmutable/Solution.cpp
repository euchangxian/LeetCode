#include <cstddef>
#include <vector>

using namespace std;
class NumArray {
 private:
  vector<int> prefix;

 public:
  NumArray(vector<int>& nums) : prefix(nums.size() + 1, 0) {
    // Since query leftRanges are inclusive
    for (size_t i = 1; i < prefix.size(); ++i) {
      prefix[i] = nums[i - 1] + prefix[i - 1];
    }
  }

  int sumRange(int left, int right) { return prefix[right + 1] - prefix[left]; }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */
