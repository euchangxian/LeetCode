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

constexpr int MOD = 1e9 + 7;
class Solution {
 public:
  int numberOfCombinationsTLE(std::string_view num) {
    // Partition nums into list of integers, such that the list is
    // non-decreasing, and no integer has leading zeros.
    // Similar to 1416. Restore the Array, but that has restrictions on the
    // individual number, whereas this requires keeping track of the previous
    // number?
    // Two State? (i, prev)
    // Similarly,
    // dfs(idx, prev) {
    //   number = 0
    //   for i in [idx, n-1]:
    //     number = number * 10 + d
    //     dfs(i+1, number) if number >= prev
    // }
    // WARNING: num.length <= 3500, which implies the largest possible number
    // may be 10^3500, which is simply too large to represent using integer
    // types.
    // String Comparison is too slow. This is essentially a 3D DP.
    const int n = num.size();

    std::vector<std::unordered_map<std::string, int>> memo(n);
    return dfs(num, memo, 0, "");
  }

 private:
  bool greaterThanOrEqual(std::string_view a, std::string_view b) {
    if (a.size() != b.size()) {
      return b.size() >= a.size();
    }

    return b >= a;
  }
  int dfs(std::string_view s,
          std::vector<std::unordered_map<std::string, int>>& memo,
          int idx,
          const std::string& prev) {
    if (idx >= s.size()) {
      return 1;
    }

    if (s[idx] == '0') {
      return 0;  // cannot start with leading 0
    }

    auto it = memo[idx].find(prev);
    if (it != memo[idx].end()) {
      return it->second;
    }

    int& ans = memo[idx][prev];
    std::string num;
    for (int i = idx; i < s.size(); ++i) {
      num += s[i];
      if (!greaterThanOrEqual(prev, num)) {
        continue;  // try to append to increase the number
      }
      ans = (1LL * ans + dfs(s, memo, i + 1, num)) % MOD;
    }
    return ans;
  }
};
