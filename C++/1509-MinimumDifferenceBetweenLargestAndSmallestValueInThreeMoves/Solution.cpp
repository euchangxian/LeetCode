#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;
class Solution {
public:
  int minDifference(vector<int> &nums) {
    if (nums.size() <= 4) {
      return 0;
    }
    sort(nums.begin(), nums.end());

    // Three moves => 4 combinations
    // Increase first three numbers
    // Increase first two, decrease last
    // Increase first, decrease last 2
    // Decrease last three numbers
    int left = 0;
    int right = nums.size() - 4;

    int minDiff = INT_MAX;
    // four scenarios, i.e. left moves up to 4th element
    while (left < 4) {
      minDiff = min(minDiff, nums[right++] - nums[left++]);
    }
    return minDiff;
  }
};

int main() {

  // 9, 31, 48, 48, 81, 92
  // 61, 72
  // 44,
  vector<int> nums = {9, 48, 92, 48, 81, 31};
  cout << Solution().minDifference(nums);
}
