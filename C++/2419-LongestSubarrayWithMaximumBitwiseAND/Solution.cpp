#include <algorithm>
#include <array>
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
  int longestSubarray(vector<int> const& nums) {
    // The bitwise AND of two numbers is always smaller than both.
    // Therefore, find the maximum element. Find the longest contiguous
    // subarray with that maximum element.
    int maxElem = 0;
    int maxSize = 0;
    int currContiguous = 0;
    for (int const& num : nums) {
      if (num > maxElem) {
        maxElem = num;
        currContiguous = 0;

        // New maximum found, previous contiguous subarray not valid.
        maxSize = 0;
      }

      if (num == maxElem) {
        ++currContiguous;
      } else {
        currContiguous = 0;
      }

      maxSize = max(maxSize, currContiguous);
    }
    return maxSize;
  }
};
