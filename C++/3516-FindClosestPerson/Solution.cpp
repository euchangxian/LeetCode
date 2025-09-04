#include <cmath>

class Solution {
 public:
  int findClosest(int x, int y, int z) {
    // x, y, z represents the positions of three people on a number line.
    // Both Person 1 and Person 2 move towards Person 3 at the same speed.
    // Determine which person reaches Person 3 first
    // - Return 1 if Person1 reaches first
    // - Return 2 if Person2 reaches first
    // - Return 0 if both arrive at the same time.
    int dist1 = std::abs(x - z);
    int dist2 = std::abs(y - z);
    if (dist2 < dist1) {
      return 2;
    }
    return dist1 < dist2;
  }
};
