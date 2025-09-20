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

class Solution {
 public:
  bool canCross(std::vector<int>& stones) {
    // stones[i] represent the position of a stone.
    // - Frog can jump onto a stone, not into the water.
    // - stones[i] > stones[i-1] for all i.
    // - Frog starts at stones[0], assume the first jump to reach that stone
    //   was 1 unit.
    // - If the frog's last jump was k units, then its next jump must be either
    //   k-1, k, or k+1 units forward.
    // Note the constraints:
    // - stones.length <= 2000
    // - stones[i] <= 2^31 - 1, i.e., INT_MAX
    //
    // Feels like some mix of Longest Increasing Subsequence,
    //                        Longest Arithmetic Subsequence
    //
    // Naively, at each stone i, with a previous jump of k units:
    // - jump to stone[j] if stone[j] - stone[i] == k-1 || k || k+1
    // The costly part is finding stone[j] such that it is k-1 | k | k+1
    // distance away.
    // Though, with a sorted array, a binary search would suffice.
    // Alternatively, a Map? Since we only need to look for 3 values.
    // Much faster.
    const int n = stones.size();
    std::vector<std::vector<bool>> memo(n + 1, std::vector<bool>(n + 1, false));
    std::unordered_set<int> seen;
    for (int i = n - 1; i >= 0; --i) {
    }

    return false;
  }
};
