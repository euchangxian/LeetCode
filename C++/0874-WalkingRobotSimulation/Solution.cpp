#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class Solution {
 private:
  long long encode(int x, int y) {
    // Interesting way to pack two 32-bits integer into one 64-bit long long
    // The upper 32 bits is set to the bits of x, while the lower 32 bits is
    // set to y
    // 0xFFFFFFFF is 32 bits of 1. Suffix with LL to denote long long, 64 bits
    return ((long long)x << 32 | (y & 0xFFFFFFFFLL));
  }

 public:
  int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
    // Infinite XY-plane
    unordered_set<long long> obstaclesSet;
    for (auto const& obstacle : obstacles) {
      obstaclesSet.insert(encode(obstacle[0], obstacle[1]));
    }

    // North, Right, South, Left. NOTE this is not ROW, COLUMN, but XY coords
    vector<pair<int, int>> const directions = {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    int dir = 0;
    pair<int, int> current = {0, 0};
    int maxDistance = 0;
    for (auto const& command : commands) {
      if (command == -2) {
        dir = ((dir - 1) + 4) % 4;
      } else if (command == -1) {
        dir = ((dir + 1) + 4) % 4;
      } else {
        auto const& [dx, dy] = directions[dir];
        for (int k = 0; k < command; ++k) {
          if (obstaclesSet.count(
                  encode(current.first + dx, current.second + dy))) {
            break;
          }
          current.first += dx;
          current.second += dy;
        }
        maxDistance = max(maxDistance, (current.first * current.first) +
                                           (current.second * current.second));
      }
    }

    return maxDistance;
  }
};
