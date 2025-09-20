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
  int cutOffTree(std::vector<std::vector<int>>& forest) {
    // m x n matrix
    // 0 -> cell cannot be walked through
    // 1 -> empty cell, can be walked through
    // >1-> tree, and the number represents the height.
    // In one step, walk any cardinal direction, and if in a tree-cell, can
    // choose to cut it off.
    // Trees must be cut off from shortest to tallest, and when cut, its value
    // becomes 1.
    // Starting from (0, 0), return the minimum number of steps to walk to
    // cut off all the trees, or -1 if not possible.
    //
    // Input is generated such that no two trees have the same height, and at
    // least one tree needs to be cut off.
    // 1 <= m,n <= 50
    //
    // Confusing. Seems trivial no? Collect all the points, then do simulation
    // from lowest height to highest height. Ah, difficult to handle unwalkable
    // cells.
  }
};
