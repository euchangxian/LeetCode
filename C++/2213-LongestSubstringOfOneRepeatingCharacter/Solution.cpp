#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <deque>
#include <functional>
#include <iostream>
#include <istream>
#include <iterator>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
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
  std::vector<int> longestRepeating(std::string_view s,
                                    std::string_view queryCharacters,
                                    std::vector<int>& queryIndices) {
    // 0 indexed string s, and a length-k queryCharacters and queryIndices.
    // The ith query updates the character in s at index queryIndices[i] to
    // queryCharacters[i].
    // Want: array of length k where arr[i] is the length of the longest
    // substring consisting of only 1 character, after the ith query is done.
    // ...
    // Hm.
    // Dynamic Data. Interval queries. Segment Tree? Everything is a nail...
    // IDK IDK IDK IDK IDK
    //
    auto zipped = std::ranges::views::zip(queryIndices, queryCharacters);
    for (auto [idx, nc] : zipped) {
    }
  }
};
