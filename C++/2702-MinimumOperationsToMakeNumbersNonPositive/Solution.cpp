#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution {
private:
  bool feasible(const std::vector<int> &nums, const int &x, const int &y,
                const int64_t ops) {
    // x > y
    const int64_t threshold{x - y};
    const int64_t base{ops * y}; // the minimum decrement on a number

    int64_t xOpsRequired{0};
    for (const int64_t &num : nums) {
      // Count the number of times required to minus y on this number to reduce
      // it to < 0
      // Ceiling division since at least one operation is required
      xOpsRequired +=
          (std::max(static_cast<int64_t>(0), (num - base + threshold - 1)) /
           threshold);
    }

    return xOpsRequired <= ops;
  }

public:
  int minOperations(std::vector<int> &nums, int x, int y) {
    // Similar to the Flower Blooming/Bouquet question with a little twist
    // where one number is decremented by y, others are decremented by x
    int left = 1;
    int right = *std::max_element(nums.begin(), nums.end());

    while (left < right) {
      int mid = left + (right - left) / 2;

      if (!feasible(nums, x, y, mid)) {
        // Ops need to be increased
        left = mid + 1;
      } else {
        right = mid;
      }
    }

    return left;
  }
};
