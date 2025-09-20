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
  int maxResult(std::vector<int>& nums, int k) {
    // jump at most k steps forward, i.e., any index [i+1, min(n-1, i+k)].
    // Score is the sum of indices visited.
    // -1E4<=nums[i]<=1E4
    // sliding window maximum of size K.
  }
};
