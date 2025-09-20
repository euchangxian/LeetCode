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
  std::vector<int> maximizeXor(std::vector<int>& nums,
                               std::vector<std::vector<int>>& queries) {
    // queries[i] = [x, m]
    // answer[i] is the max(x^a), where a is an element of nums that do not
    // exceed m, i.e., a<=m
    //
    // We can do offline queries. Then keep track of the running bitwise
    // frequency.

    // sort by ascending queries.
    std::ranges::sort(queries, {}, [](const auto& v) { return v[1]; });
  }
};
