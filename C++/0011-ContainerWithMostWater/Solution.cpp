#include <vector>

using namespace std;
class Solution {
public:
  int maxArea(vector<int> &height) {
    int left = 0;
    int right = height.size() - 1;

    int result = 0;
    while (left < right) {
      int currentArea = min(height[left], height[right]) * (right - left);
      result = max(result, currentArea);

      if (height[left] < height[right]) {
        ++left;
      } else {
        --right;
      }
    }
    return result;
  }
};
