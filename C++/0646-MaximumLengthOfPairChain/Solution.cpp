#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  int findLongestChain(std::vector<std::vector<int>>& pairs) {
    // pairs[i] = [left, right], left < right
    //
    // A pair p2 = [c, d] is said to follow pair p1 = [a, b] if b < c.
    // Like intervals.
    // Find length of longest chain, select pairs in any order.
    // Sort? by start. Remove overlaps. Does not guarantee longest.
    // Longest Increasing Subsequence? Need to consider pairs though.
    // Sort by start (tie-broken with earlier end).
    // Insert first pair.right
    // Then, for each pair in [2..n]:
    //   consider pair.left.
    //   if curr.left > lis.back(), then trivially extend.
    //   Otherwise, try to replace with curr.right (if curr.right is small)
    std::vector<int> lis;
    lis.reserve(pairs.size());

    std::sort(pairs.begin(), pairs.end());
    lis.push_back(pairs.front()[1]);
    for (int i = 1; i < pairs.size(); ++i) {
      const int left = pairs[i][0];
      const int right = pairs[i][1];
      if (left > lis.back()) {
        lis.push_back(right);
        continue;
      }

      auto it = std::lower_bound(lis.begin(), lis.end(), right);
      if (it != lis.end()) {
        *it = right;
      }
    }
    return static_cast<int>(lis.size());
  }
};
