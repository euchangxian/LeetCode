#include <algorithm>
#include <unordered_set>
#include <vector>

class Solution {
 public:
  int robotSim(std::vector<int>& commands,
               std::vector<std::vector<int>>& obstacles) {
    // Infinite XY-plane
    std::unordered_set<long long> obstaclesSet;
    for (const auto& obstacle : obstacles) {
      obstaclesSet.insert(encode(obstacle[0], obstacle[1]));
    }

    // North, Right, South, Left. NOTE this is not ROW, COLUMN, but XY coords
    const std::vector<std::pair<int, int>> directions = {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    int dir = 0;
    std::pair<int, int> current = {0, 0};
    int maxDistance = 0;
    for (int command : commands) {
      if (command == -2) {
        dir = ((dir - 1) + 4) % 4;
      } else if (command == -1) {
        dir = ((dir + 1) + 4) % 4;
      } else {
        const auto [dx, dy] = directions[dir];
        for (int k = 0; k < command; ++k) {
          if (obstaclesSet.count(
                  encode(current.first + dx, current.second + dy))) {
            break;
          }
          current.first += dx;
          current.second += dy;
        }
        maxDistance =
            std::max(maxDistance, (current.first * current.first) +
                                      (current.second * current.second));
      }
    }

    return maxDistance;
  }

 private:
  long long encode(int x, int y) {
    // Interesting way to pack two 32-bits integer into one 64-bit long long
    // The upper 32 bits is set to the bits of x, while the lower 32 bits is
    // set to y
    // 0xFFFFFFFF is 32 bits of 1. Suffix with LL to denote long long, 64 bits
    return ((long long)x << 32 | (y & 0xFFFFFFFFLL));
  }
};
