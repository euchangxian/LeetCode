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

using i64 = long long;
class Solution {
 public:
  i64 numberOfSubarrays(std::vector<int>& nums) {
    // Number of subarrays of nums where the first and last elements of the
    // subarray are equal to the largest element in the subarray.
    // Sliding Window Maximum allows us to maintain the maximum of the
    // subarray, but how do we decide when to extend right, or shrink left?
    // Counting all the indices of each element's occurences seem viable,
    // along with some combinatorics.
    // i.e., 1 + 2 + ... + n = n*(n+1)/2 if an element occurs n times.
    // Feels too trivial?
    // e.g., {6, 26, 6} is not valid, since 26 > 6. Such a big miss.
    std::unordered_map<int, int> freq;
    freq.reserve(nums.size());
    for (int x : nums) {
      ++freq[x];
    }

    i64 result = 0;
    for (const auto& [_, k] : freq) {
      result += static_cast<i64>(k) * (k + 1) / 2LL;
    }
    return result;
  }
};
