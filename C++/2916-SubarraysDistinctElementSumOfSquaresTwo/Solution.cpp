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
  int sumCounts(std::vector<int>& nums) {
    // The distinct count of nums[i..j] is the number of distinct values in
    // nums[i..j]
    // Return the sum of SQUARES of distinct count of ALL subarrays of nums.
    //
    // Naively enumerating all subarrays will take O(N^2) and is too slow.
    //
    // Hm.
  }
};
