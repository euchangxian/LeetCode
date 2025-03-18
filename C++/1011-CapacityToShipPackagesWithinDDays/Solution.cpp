#include <algorithm>
#include <vector>

class Solution {
 public:
  int shipWithinDays(std::vector<int>& weights, int days) {
    // Insight: There exist a k weight, such that if
    // canShipWithinDays(k) == true, then canShipWithinDays(k + 1) == true
    // Therefore, binary search can be applied
    int left = 0;
    int right = 0;
    for (int num : weights) {
      left = std::max(left, num);
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

 private:
  bool canShipWithinDays(const std::vector<int>& weights,
                         int days,
                         int capacity) {
    // Weights are loaded in order of occurence. No need to sort
    int requiredDays = 1;
    int currentLoad = 0;
    for (int weight : weights) {
      currentLoad += weight;

      if (currentLoad > capacity) {
        // Wait for next day
        currentLoad = weight;
        ++requiredDays;
      }
    }
    return requiredDays <= days;
  }
};
