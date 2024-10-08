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
  double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    // Intuition: Finding the median is equivalent to finding the right "cut"
    // point in both arrays that divides all elements into two equal halves.
    //
    // Visualizing the problem:
    // nums1: [.... left1 ....] cut1 [.... right1 ....]
    // nums2: [.... left2 ....] cut2 [.... right2 ....]
    // We want: all elements in (left1 + left2) <= all elements in (right1 +
    // right2)
    //
    // Insight: If we find the correct position for cut1, we automatically know
    // where cut2 should be to keep the left and right sides balanced.
    //
    // Binary search property:
    // As we move cut1 to the right, cut2 must move left to maintain balance,
    // and vice versa. This creates a monotonic relationship we can exploit with
    // binary search.
    //
    // What we search for: search for the position of cut1 that satisfies:
    // a) max(left1) <= min(right2)
    // b) max(left2) <= min(right1)
    //
    // If these conditions are met, we've found the correct partition because:
    // - All elements in left1 are <= all elements in right1 (sorted array
    //   property)
    // - All elements in left2 are <= all elements in right2 (sorted array
    //   property)
    // - max(left1) <= min(right2) and max(left2) <= min(right1)
    // Therefore, all elements in (left1 + left2) <= all elements in
    // (right1 + right2)
    //
    // Updating the pointers:
    // - If max(left1) > min(right2), move cut1 to the left
    //   (This automatically moves cut2 to the right)
    // - If max(left2) > min(right1), move cut1 to the right
    //   (This automatically moves cut2 to the left)
    //
    // - When we move cut1, we're essentially swapping an element between left1
    //   and right1
    // - This swap can only affect the max(left1) and min(right1)
    // - The same is true for cut2 with respect to left2 and right2
    // - Therefore, checking these specific values is sufficient to determine
    //   the correct direction

    // Once the correct cuts are found, handle odd/even length cases.
    // - If total elements is odd: median = max(left1.last, left2.last)
    // - If total elements is even:
    // median = (max(left1.last, left2.last)+min(right1.first, right2.first))/ 2

    // Ensure nums1 is smaller
    if (nums1.size() > nums2.size()) {
      swap(nums1, nums2);
    }

    int left = 0;
    // Note no -1. The partition could lie between the two arrays. I.e.,
    // the entirety of nums1 lies to the left of the median.
    int right = nums1.size();

    // Note LTE instead of LT. This is because we include the return condition
    // into the loop
    while (left <= right) {
      int partition1 = left + ((right - left) / 2);

      // Note the +1 => Ceiling division. This is to compensate for the floor
      // division to get partition1
      int partition2 = (nums1.size() + nums2.size() + 1) / 2 - partition1;

      int left1Max = partition1 > 0 ? nums1[partition1 - 1] : INT_MIN;
      int right1Min = partition1 < nums1.size() ? nums1[partition1] : INT_MAX;

      int left2Max = partition2 > 0 ? nums2[partition2 - 1] : INT_MIN;
      int right2Min = partition2 < nums2.size() ? nums2[partition2] : INT_MAX;

      if (left1Max <= right2Min && left2Max <= right1Min) {
        // Correct partition
        // Handle even/odd cases
        if ((nums1.size() + nums2.size()) % 2) {
          // Odd
          return max(left1Max, left2Max);
        }
        return (max(left1Max, left2Max) + min(right1Min, right2Min)) / 2.0;
      }

      // The cut is too much to the right, overlapping with right2
      if (left1Max > right2Min) {
        // partition1 should lie to the left
        right = partition1 - 1;
      } else {
        left = partition1 + 1;
      }
    }

    // Should not reach this line
    return -1;
  }
};
