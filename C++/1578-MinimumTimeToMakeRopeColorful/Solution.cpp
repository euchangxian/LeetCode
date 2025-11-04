#include <algorithm>
#include <string_view>
#include <vector>

class Solution {
 public:
  int minCost(std::string_view colors, std::vector<int>& neededTime) {
    // n balloons arranged on a rope.
    // colors[i] is the color of the ith balloon.
    // Alice wants no two consecutive balloons to be same color.
    // Bob can remove the ith balloon using neededTime[i].
    // Return minimum time to make balloon colorful.
    const auto n = static_cast<int>(neededTime.size());

    int cost = 0;
    int i = 0;
    int j = 0;
    while (i < n && j < n) {
      int currCost = 0;
      int currMax = 0;
      while (j < n && colors[i] == colors[j]) {
        currCost += neededTime[j];
        currMax = std::max(currMax, neededTime[j]);
        ++j;
      }

      cost += currCost -= currMax;
      i = j;
    }
    return cost;
  }
};
