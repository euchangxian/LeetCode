#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstdint>
#include <deque>
#include <functional>
#include <iostream>
#include <istream>
#include <iterator>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

constexpr int MAX_XY = 100;
constexpr std::array<std::array<int, 2>, 4> directions{{
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0},
}};

class Solution {
 public:
  int minDayskVariants(std::vector<std::vector<int>>& points, int k) {
    // points[i] = [x, y] indicating a virus originating at (x, y) on day 0.
    // Multiple viruses can originate at the same point.
    // Spread to cardinal directions on each day.
    // Return minimum number of days for ANY (NOT ALL) points to contain at
    // least k of the unique virus variants.
    //
    // Similar to 317. Shortest Distance From All Buildings, particularly,
    // BFS from Building cells, maintain at each cell (dist, reachable)
    // Similarly, we can BFS from all viruses (compress same-locations),
    // maintain at each cell (time, uniqueViruses)
    //
    // 100 * 100 grid.
    // Let grid[r][c] == 0 indicate uninfected
    //                  >0 indicate number of unique viruses starting at (r, c)
    //                  <0 indicate number of unique viruses infecting this pt.
    std::array<std::array<int, MAX_XY + 1>, MAX_XY + 1> grid{};
    for (const auto& point : points) {
      ++grid[point[0]][point[1]];
    }

    // {x, y, uniqueViruses}
    std::queue<std::tuple<int, int, int>> frontier;
    for (int x = 1; x <= MAX_XY; ++x) {
      for (int y = 1; y <= MAX_XY; ++y) {
        if (grid[x][y] > 0) {
          frontier.emplace(x, y, grid[x][y]);
        }
      }
    }

    int time = 1;
    while (!frontier.empty()) {
      int sz = frontier.size();
      while (sz--) {
        auto [x, y, unique] = frontier.front();
        frontier.pop();

        for (const auto [dx, dy] : directions) {
          int nx = x + dx;
          int ny = y + dy;

          if (nx < 1 || ny < 1 || nx > MAX_XY || ny > MAX_XY) {
            continue;
          }
        }
      }
      ++time;
    }
  }
};
