#include <algorithm>
#include <vector>

class Solution {
 public:
  int maxArea(std::vector<int>& height) {
    int left = 0;
    int right = height.size() - 1;

    int result = 0;
    while (left < right) {
      int currentArea = std::min(height[left], height[right]) * (right - left);
      result = std::max(result, currentArea);

      if (height[left] < height[right]) {
        ++left;
      } else {
        --right;
      }
    }
    return result;
  }
};
