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
  int minSwaps(vector<int> &nums) {
    int n = nums.size();

    int windowSize = 0; // number of ones
    for (auto const &num : nums) {
      if (num) {
        ++windowSize;
      }
    }

    int maxInWindow = 0;
    int inWindow = 0;

    int l = 0;
    for (int r = 0; r < n + windowSize - 1; ++r) {
      if (nums[r % n]) {
        // consider the element at the right of the window
        ++inWindow;
      }

      if (r - l + 1 > windowSize) {
        if (nums[l++]) {
          --inWindow;
        }
      }

      maxInWindow = max(maxInWindow, inWindow);
    }

    return windowSize - maxInWindow;
  }
};

