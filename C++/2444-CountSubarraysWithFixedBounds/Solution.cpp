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
  long long countSubarrays(vector<int> &nums, int minK, int maxK) {
    // To count the number of subarrays where all the elements in the subarray
    // are within the range [minK, maxK],
    //
    // Consider a valid subarray. What happens if the subarray is extended?
    // 1. If an element within the range [minK, maxK] is added, its still valid
    // 2. If an element outside the range is added, the entire subarray becomes
    //    invalid, and no more subarrays can be formed from the previous minK
    //    and maxK.
    //
    // Thus, we need to keep track of the index of the last seen minK and maxK.
    // This allows us to determine the validity of the next element added to the
    // subarray.
    // To simplify the counting, introduce a variable badIdx, that indicates the
    // index of the last seen element that violates the validity. (otherwise, by
    // moving both the minK and maxK index, we have to introduce complex logic
    // to look for valid minK and maxK and restart the count)

    int prevMin = -1;
    int prevMax = -1;
    int prevBad = -1;

    long long count = 0;
    for (int i = 0; i < nums.size(); ++i) {
      if (nums[i] < minK || nums[i] > maxK) {
        prevBad = i;
        continue;
      }

      if (nums[i] == minK) {
        prevMin = i;
      }

      if (nums[i] == maxK) {
        prevMax = i;
      }

      // WLOG,
      // if prevMin < prevBad < prevMax => Add 0
      // if prevBad < prevMin < prevMax => Add (prevMin - prevBad)
      // This is because each element between prevMin and prevBad can be the
      // left-most/start of the valid subarray
      // if prevMin < prevMax < prevBad => Add 0
      count += max(0, // handle the case where prevBad occurs after maxK, WLOG
                   min(prevMin, prevMax) - prevBad);
    }
    return count;
  }
};
