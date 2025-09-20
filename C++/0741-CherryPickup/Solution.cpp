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
  int cherryPickup(std::vector<std::vector<int>>& grid) {
    // Suspicious. not BFS twice?
    // Probably because we cant guarantee that the maximum path from top-left
    // to bottom-right, plus the maximum path AFTER will result in the best
    // score.
    // [[0, 1, 1]      [[0, 1, 1]      [[0, 1, 1]
    //  [1, 1, 1]  -->  [0, 0, 0]  -->  [0, 0, 0]   == 5. Not optimal.
    //  [1, 1, 0]]      [1, 1, 0]]      [0, 0, 0]]
    //
    // [[0, 1, 1]      [[0, 1, 1]      [[0, 0, 0]
    //  [1, 1, 1]  -->  [0, 1, 1]  -->  [0, 1, 0]   == 6
    //  [1, 1, 0]]      [0, 0, 0]]      [0, 0, 0]]
    //
    // Naively, DFS/backtrack twice, from top-left to bottom-right, then
    // from bottom-right to top-left.
    // Amount of branching will be too crazy.
  }
};
