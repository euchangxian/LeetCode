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
  int maxProduct(vector<int> &nums) {
    int n = nums.size();

    int maxProd = nums[0];
    int minSoFar = maxProd;
    int maxSoFar = maxProd;

    // Similar to Kadane's Algorithm:
    // At each step, there are two decisions:
    // 1. Extend the previous subarray, or
    // 2. Start a new subarray
    //
    // Although the product of the previous subarray may be negative,
    // there is a possibility that nums[i] is also negative, resulting in a
    // large product.
    for (int i = 1; i < n; ++i) {
      if (nums[i] < 0) {
        // if the current number is negative, then maxSoFar * nums[i] would
        // actually result in a negative number (if maxSoFar is positive).
        // Swapping allows us to cleanly retain the max and min semantics
        // below.
        swap(minSoFar, maxSoFar);
      }

      minSoFar = min(nums[i], minSoFar * nums[i]);
      maxSoFar = max(nums[i], maxSoFar * nums[i]);

      maxProd = max(maxProd, maxSoFar);
    }

    return maxProd;
  }
};
