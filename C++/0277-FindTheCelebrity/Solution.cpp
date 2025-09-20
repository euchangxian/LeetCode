#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

/* The knows API is defined for you.
      bool knows(int a, int b); */
bool knows(int a, int b);

class Solution {
 public:
  int findCelebrity(int n) {
    // O(n) calls to knows to figure out the node with 0 outgoing edges and
    // n-1 incoming edges.
    // Feels like Find Majority.
    // Given an adjacency matrix (hypothetically), what do we find?
  }
};
