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

class Solution {
 public:
  int shortestSubarray(std::vector<int>& nums, int k) {
    // length of shortest non-empty subarray with sum at least k. -1 otherwise.
    // problem is nums[i] can be negative, naive sliding window would not work.
    // e.g., [2, -1, 2]
    //
    // what about prefixes?
    // nums = [2, -1, 2, 1]
    // prefix=[2, 1, 3, 4],
    // => 4 - 1 >= k, subarray {2, 1}.
    //
    // but finding '1' is non trivial? since we want at least k. Binary search?
    // not monotonic due to negative numbers.
    //
    // But it seems that prefixes are on the right track, since we can avoid
    // recomputing sums of a subarray repeatedly.
    // Isnt this just Kadane's, each time the maximum subarray sum >= k, then
    // we add one to the count. Not exactly. By aiming for the maximum, we
    // may under-count.
  }
};
