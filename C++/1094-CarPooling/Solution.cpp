#include <array>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  bool carPooling(std::vector<std::vector<int>>& trips, int capacity) {
    // trips[i] = [numPassengers, from, to]
    // return true if the car with capacity can pick up and drop off ALL
    // passengers.
    std::array<int, 1'002> points{};
    for (const auto& trip : trips) {
      const auto num = trip[0];
      const auto from = trip[1];
      const auto to = trip[2];

      points[from] += num;
      points[to] -= num;
    }

    int sum = 0;
    for (int count : points) {
      sum += count;
      if (sum > capacity) {
        return false;
      }
    }
    return true;
  }
};
