#include <array>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  int numberOfPoints(std::vector<std::vector<int>>& nums) {
    // nums[i] = [start, end], inclusive.
    // Line Sweep.
    // Counting the number of points is not straightforward? Since its the
    // implicit range from minX to maxX.
    // Suppose at each x-coordinate we have the number of cars that cover that
    // point.
    // The number can only be >= 0.
    // If it is 0, then we can conclude that this point until the next point
    // has no cars covering (the next point must be the start of another Car)
    // Thus, we can maintain the number of points that are NOT covered,
    // then take (maxX - minX) which represents the total number of points,
    // minus the sum of uncovered points.
    //
    // Can be further optimized by using a fixed size array of size 102, that
    // represent the maximum number of points given by the input constraints,
    // 1 <= start, end <= 100.
    // That way, we can directly count the number of points with
    // intersection > 0

    // {coordinate, count}
    std::array<int, 102> points{};
    for (const auto& num : nums) {
      ++points[num[0]];
      --points[num[1] + 1];  // exclusive end
    }

    int covered = 0;
    int cars = 0;
    for (const auto count : points) {
      cars += count;

      if (cars) {
        ++covered;
      }
    }
    return covered;
  }
};
