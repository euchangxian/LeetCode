#include <algorithm>

using i64 = long long;
class Solution {
 public:
  i64 distributeCandies(i64 n, i64 limit) {
    // Given two positive integers n and limit.
    // Return the number of ways to distribute n candies among 3 children, such
    // that no children get more than limit candies.
    // 1 <= n, limit <= 10^6
    //
    // 3-tuple to represent state. (x, y, z)
    // Naively, for each candy up to N, there are 3 choices.
    // Need a smarter way though.
    //
    // Feels math-y instead of simulation.
    // Find the number of ways such that A + B + C == n
    // Give B candies first. Then there will be (N-B) candies left to
    // distribute.
    //
    i64 result = 0LL;

    // distribute to B.
    for (i64 B = 0LL; B <= std::min(n, limit); ++B) {
      if (n - B <= 2LL * limit) {  // distribute to two children.
        // Find all possible ways to split between A and C, where A (or C) can
        // take up values in the range:
        // [lower_bound..upper_bound]
        // Let R = N-B, i.e., remaining candies after distributing to B.
        // Then,
        // lower_bound = R-limit, i.e., give limit to C, the rest to A.
        // upper_bound = R, i.e., give all remainder to A.
        // Clamp the values,
        // upper_bound - lower_bound = min(R, limit) - max(R-limit, 0)
        result += std::min(n - B, limit) - std::max(0LL, n - B - limit) + 1LL;
      }
    }
    return result;
  }
};
