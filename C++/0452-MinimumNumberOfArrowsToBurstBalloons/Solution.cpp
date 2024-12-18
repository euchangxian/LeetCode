#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  int findMinArrowShots(std::vector<std::vector<int>>& points) {
    // find the maximum intersection between lines.
    // NOPE. Not so straightforward.
    // Visualizing the line, we want to shoot at each PEAK. i.e., the points
    // where most balloons intersect.
    // Hm. Line Sweep isnt very appropriate.
    // Note that we want to burst EVERY balloon. Thus, one observation we can
    // make is that we want to shoot an arrow at every LOCAL peak, visualizing
    // the points as the number of balloons intersecting. (try to convince
    // yourself that we want the local peak).
    // LOCALLY optimal => Greedy.
    // Again, visualize the balloons as ranges on the line. When we sort by
    // ascending order of start, we have to make a choice as to whether we want
    // to shoot an arrow at the point, or not. This is DP.
    // However, sorting by ascending orders of ending position lets us greedily
    // shoot an arrow at THAT ending position, and all balloons that intersect
    // with that position will be popped, which is our local optima we want.
    std::sort(points.begin(), points.end(),
              [](const std::vector<int>& a, const std::vector<int>& b) -> bool {
                return a[1] < b[1];
              });

    int arrows = 1;
    int prevEnd = points[0][1];
    for (int i = 1; i < points.size(); ++i) {
      if (points[i][0] <= prevEnd) {
        // balloon can be burst by shooting at the prevEnd coordinate.
        continue;
      }

      ++arrows;
      prevEnd = points[i][1];
    }
    return arrows;
  }
};
