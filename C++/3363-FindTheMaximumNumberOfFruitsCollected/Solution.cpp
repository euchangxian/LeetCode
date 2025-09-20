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
  int maxCollectedFruits(std::vector<std::vector<int>>& fruits) {
    // n x n grid of rooms.
    // fruits[i][j] represent number of fruits in the (i,j)-th room.
    // 3 Children start at (0, 0), (0, n-1), (n-1, 0).
    // Children make exactly n-1 moves to reach (n-1, n-1)
    // Move diagonally or cardinally.
    // Fruits can only be collected once.
    // Return the maximum number of fruits that can be collected in total.
    //
    // Hm. The (0,0)-th children can only move diagonally right?
    // i.e., from (i, j) to (i+1, j+1).
    // The (0, n-1)-th child must always make a move such that (i+1, ...)
    // and likewise for (n-1, 0)-th child: (..., j+1)
  }
};
