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
  int componentValue(std::vector<int>& nums,
                     std::vector<std::vector<int>>& edges) {
    // Given undirected tree with n nodes labelled from 0 to n-1,
    // where nums[i] represent the value of the ith node,
    // edges[i] = [u, v] indicate an edge between node u and node v.
    // Delete the maximum number of edges such that every connected component
    // in the tree has the same value.
    //
    // n <= 2 * 10E4
    // nums[i] <= 50
  }
};
