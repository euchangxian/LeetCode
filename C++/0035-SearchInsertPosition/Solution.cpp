#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class Solution {
public:
  int searchInsert(vector<int> &nums, int target) {
    // Given sorted nums, find the index k in nums such that
    // target <= nums[k]
    // i.e., Binary search the minimal value of k.
    int left = 0;
    int right = nums.size(); // not minus 1. k can be appended.

    while (left < right) {
      int mid = left + (right - left) / 2;
      if (nums[mid] < target) {
        left = mid + 1;
      } else {
        right = mid;
      }
    }
    return left;
  }
};
