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
  bool find132pattern(std::vector<int>& nums) {
    // start -> up -> down such that i < j < k, nums[i] < nums[k] < nums[j]

    // monotonically increasing
    // If we can have a sequence of pop -> !stk.empty(), then we have our answer
    std::vector<int> stk;
    for (int x : nums) {
      bool hasPop = false;
      while (!stk.empty() && stk.back() >= x) {
        hasPop = true;
        stk.pop_back();
      }

      if (hasPop && !stk.empty()) {
        return true;
      }

      stk.push_back(x);
    }
    return false;
  }
};
