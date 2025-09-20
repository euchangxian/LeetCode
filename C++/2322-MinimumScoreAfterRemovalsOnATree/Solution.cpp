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
  int minimumScore(std::vector<int>& nums,
                   std::vector<std::vector<int>>& edges) {
    // Given an undirected tree with N nodes, N-1 edges.
    // Given nums of length N, nums[i] represent the value of the ith node.
    // Remove two distinct edges of the tree to form three connected components.
    // For a pair of removed edges:
    // 1. Get the XOR of each connected component
    // 2. The score is equal to the largest XOR minus the smallest XOR.
    // Return the minimum score.
    auto n = static_cast<int>(nums.size());
  }
};
