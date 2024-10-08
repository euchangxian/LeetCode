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
  // {4, 1, 2, 3}, {3, 4, 1, 2}, {2, 3, 4, 1}, {1, 2, 3, 4}
  int findMin(vector<int>& nums) {
    // When the array is rotated k times, it causes the array to be splitted
    // into two SORTED subarrays, where elements in the left subarray {0, k - 1}
    // is greater than elements in the right subarray {k, n - 1}.
    // As such, by mapping each index as to whether its greater than the element
    // at index k, the monotonic property can be observed: {T, ..., T, F, ...}
    // where the first occurence of F is k, the number of rotations.
    // It is also the minimum element.
    int left = 0;
    int right = nums.size() - 1;

    while (left < right) {
      int mid = left + (right - left) / 2;

      // Be mindful of the conditions. If nums[left] > nums[right],
      // then k lies in the right-half.
      if (nums[mid] > nums[right]) {
        left = mid + 1;
      } else {
        right = mid;
      }
    }

    return nums[left];
  }
};
