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
#include <limits>
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

class Solution {
 public:
  int lenOfVDiagonal(std::vector<std::vector<int>>& grid) {
    // n x m grid.
    // grid[i][j] = 0 | 1 | 2
    // A V-shaped diagonal segment is defined as:
    // - Segment starts with 1
    // - Subsequent elements follow this infinite sequence 2, 0, 2, 0, ...
    // - The segment:
    //   - starts along a diagonal direction
    //   - continues the sequence in the same diagonal direction
    //   - makes at most one clockwise 90degree turn to another diagonal
    //     direction
    // Return the longest V-shaped diagonal segment.
    //
    // Hm.
    // - We have limited starting points.
    // - We always want to make the clockwise turn if possible.
    //
    // Naively, collect all coordinates of '1's.
    // Do a DFS in cardinal directions if possible.
    // We possibly visit the cells multiple times though. Seems DP-like.
    // Except we want to maintain the direction that we visited the cell from?
  }
};
