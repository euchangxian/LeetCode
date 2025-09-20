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

constexpr int MOD = 1E9 + 7;
class Solution {
 public:
  int numSubseq(std::vector<int>& nums, int target) {
    // Return the number of non-empty subsequences of nums such that the
    // sum of the min and max element on it is <= target, mod 1E9+7.
    //
    // A subsequent of size 1 is trivially valid.
    // If an element x is seen such that min <= x <= max, then that x can
    // trivially form valid subsequences with all existing valid subsequences.
    // An element that is the current min/max may not be instantly ruled out.
    // We may encounter an element that allows us to satisfy the condition.
  }
};
