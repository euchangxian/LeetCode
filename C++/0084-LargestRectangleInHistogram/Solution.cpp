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
  int largestRectangleArea(vector<int> &heights) {
    // Monotonically non-decreasing stack
    // When the current height is shorter than the top of the stack,
    // then pop the elements in the stack to find the max area.
    // Contains the index of the left boundary of the current rectangle
    // {leftIndex, height}
    stack<pair<int, int>> stk;

    heights.push_back(0); // avoid having to empty the stack afterwards
    int maxArea = 0;
    for (int r = 0; r < heights.size(); ++r) {
      int leftBound = r;
      while (!stk.empty() && heights[r] < stk.top().second) {
        auto const &[l, height] = stk.top();
        stk.pop();

        maxArea = max(maxArea, height * (r - l));

        // Due to the monotonically non-decreasing property,
        // the current height at index r can be extended all the way to the
        // index of the last popped height. Try visualizing.
        leftBound = l;
      }
      stk.push({leftBound, heights[r]});
    }

    return maxArea;
  }
};