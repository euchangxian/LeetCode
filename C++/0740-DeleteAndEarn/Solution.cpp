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
  int deleteAndEarn(vector<int>& nums) {
    // Naive solution:
    // 1. Pick idx, recurse on nums \ {(nums[idx] - 1) U (nums[idx] + 1)}
    // 2. Skip idx, recurse on nums
    // Pick the max
    //
    // What are the subproblems?
    // Seems similar to House Robber, when adjacent houses cannot be robbed;
    // adjacent buckets cannot be taken
    constexpr size_t n = 10e4 + 1;

    // Directly count the total number of points achievable by taking the
    // number
    // `{}` is an empty initializer which value-initializes elements in the
    // array.
    array<int, n> points{};
    for (auto const& num : nums) {
      points[num] += num;
    }

    int skipPrev = 0;
    int takePrev = 0;
    for (int i = 0; i < n; ++i) {
      int currMax = max(takePrev, skipPrev + points[i]);

      skipPrev = takePrev;
      takePrev = currMax;
    }

    return max(skipPrev, takePrev);
  }
};
