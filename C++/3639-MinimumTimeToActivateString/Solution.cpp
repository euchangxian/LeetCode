#include <set>
#include <string_view>
#include <vector>

using i64 = long long;
class Solution {
 public:
  int minTime(std::string_view s, std::vector<int>& order, int k) {
    // Given string s of length n, integer array order, where order is a
    // permutation of the numbers in the range [0..n-1].
    // Starting from time t=0, replace the character at index order[t] in s
    // with '*' at each time step.
    // A substring is valid if it contains at least one '*'.
    // A string is active if the total number of valid substrings is greater
    // or equal to k.
    //
    // Each timestep adds n, n-1, n-2, ... 1 valid substring.
    // We dont even need to simulate anything?
    // Nope. Wrong. Depending on the position, the number of valid substrings
    // formed is different. Adding to the front adds n. Adding to the middle
    // adds more than n (for the first one).
    // It depends on how far it is from the * on the left and the right.
    const auto n = static_cast<int>(order.size());
    std::set<int> pos{-1, n};
    for (int t = 0; t < n; ++t) {
      int idx = order[t];
      auto it = pos.lower_bound(idx);
      auto right = *it;
      auto left = *(--it);

      k -= static_cast<i64>(idx - left) * static_cast<i64>(right - idx);
      if (k <= 0) {
        return t;
      }
      pos.insert(idx);
    }
    return -1;
  }
};
