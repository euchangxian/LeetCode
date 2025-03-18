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

class Solution {
 public:
  int carFleet(int target,
               std::vector<int>& position,
               std::vector<int>& speed) {
    int n = position.size();

    std::vector<int> cars(n);
    for (int i = 0; i < n; ++i) {
      cars[i] = i;
    }

    // Sort by position closest to end first.
    // This is because the cars will take the minimum speed of the fleet.
    std::sort(cars.begin(), cars.end(),
              [&position](int i, int j) { return position[i] > position[j]; });

    int carFleets = n;  // each car is a fleet by itself at the start

    // Time taken for the car in front of the current to reach the target
    double prevTime = 0.0;
    for (int i = 0; i < n; ++i) {
      int car = cars[i];
      double time = (target - position[car]) / double(speed[car]);
      if (time <= prevTime) {
        // If the time it takes to reach the target is less, then the car will
        // catch up.
        --carFleets;
        continue;
      }

      // Otherwise, the current car becomes the choke point
      prevTime = time;
    }

    return carFleets;
  }
};
