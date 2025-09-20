#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
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

class Solution {
 public:
  std::vector<std::vector<int>> fourSum(std::vector<int>& nums, int target) {
    // Reduce to 3-Sum, then reduce to 2-Sum. Done by "choosing" the first two
    // elements.
    // But we only want unique combinations by value. Therefore, we can convert
    // nums to a set first.
    std::unordered_set<int> unique{nums.begin(), nums.end()};
    std::vector<std::vector<int>> result;

    for (auto it = unique.begin(); it != unique.end(); ++it) {
      for (auto jt = std::next(unique.begin(), 1); jt != unique.end(); ++jt) {
        int reducedTarget = target - *it - *jt;

        // 2-Sum
        for (auto kt = std::next(unique.begin(), 2); kt != unique.end(); ++kt) {
          int complement = reducedTarget - *kt;
          auto compIt = unique.find(complement);
          if (compIt != unique.end()) {
            result.push_back({*it, *jt, *kt, *compIt});
          }
        }
      }
    }

    return result;
  }
};
