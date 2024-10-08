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
 private:
  bool canShipWithinDays(vector<int> const& weights,
                         int days,
                         int const capacity) {
    // Weights are loaded in order of occurence. No need to sort
    int requiredDays = 1;
    int currentLoad = 0;
    for (int const& weight : weights) {
      currentLoad += weight;

      if (currentLoad > capacity) {
        // Wait for next day
        currentLoad = weight;
        ++requiredDays;
      }
    }
    return requiredDays <= days;
  }

 public:
  int shipWithinDays(vector<int>& weights, int days) {
    // Insight: There exist a k weight, such that if
    // canShipWithinDays(k) == true, then canShipWithinDays(k + 1) == true
    // Therefore, binary search can be applied
    int left = 0;
    int right = 0;
    for (int const& num : weights) {
      left = max(left, num);
      right += num;
    }

    while (left < right) {
      int mid = left + (right - left) / 2;

      if (!canShipWithinDays(weights, days, mid)) {
        left = mid + 1;
      } else {
        right = mid;
      }
    }
    return left;
  }
};
