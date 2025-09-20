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
  int maxPathLength(std::vector<std::vector<int>>& coordinates, int k) {
    // coordinates[i] = [x, y] indicating a point on a 2D Plane.
    // An increasing path of length m is defined as a list of points such that:
    // x_i < x_{i+1} and y_i < y_{i+1} for all 1<=i<m
    // Return the maximum length of an increasing path that contains
    // coordinates[k].
    //
    // Purely without including coordinates[k], likely a topological sort
    // to form an acyclic directed graph.
    // Then, bfs/DP to get the longest path.
    // Ah. Then just return dp[k]? Nope. Thats the longest path ending at
    // coordinates k.
    // What about something like longest increasing subsequence?
    //
    // Sorting?
    // We can sort by ascending x, tiebroken by ascending y.
    // A naive greedy may not work though. E.g,.
    // (0, 100), (1, 1), (2, 2), (3, 3), ..., (101, 101),
    // where coordinates[k] = (101, 101).
    // If we pick the first point, then all subsequent points cannot be picked.
  }
};
