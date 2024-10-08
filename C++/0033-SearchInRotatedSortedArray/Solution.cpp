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
  int search(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;

    // The elements in the left sorted subarray are all larger
    // than the elements in the right sorted subarray
    // nums[0..k] > nums[k..n];
    // Thus, for the elements at any index, if it is smaller than the
    // first element, it belongs to the right subarray nums[k..n],
    // otherwise, it belongs to the left subarray nums[0..k].
    // Thus, do a binary search to find k, the number of times the
    // array was rotated. Then determine which subarray the target
    // belongs to and binary search the relevant subarray.

    // To find k, use the sorted property.
    while (left < right) {
      int mid = left + (right - left) / 2;

      if (nums[mid] > nums[right]) {
        left = mid + 1;
      } else {
        // mid may be k
        right = mid;
      }
    }

    // distinct, dont need LTE
    // left will be the value of k
    if (target >= nums[left] && target <= nums[nums.size() - 1]) {
      right = nums.size() - 1;
    } else {
      right = left - 1;
      left = 0;
    }

    while (left < right) {
      int mid = left + (right - left) / 2;

      if (nums[mid] < target) {
        left = mid + 1;
      } else {
        right = mid;
      }
    }
    return nums[left] == target ? left : -1;
  }
};
