#include <algorithm>
#include <array>
#include <ranges>
#include <string_view>

class Solution {
 public:
  bool checkStrings(std::string_view s1, std::string_view s2) {
    // Two strings of length n, lowercase english letters.
    // Any number of times:
    // - Choose any two indices i, j such that i<j, and j-i is even, and swap
    //   the two characters.
    // Return true if s1 can be made equal to s2.
    //
    // Equality of even and odd indices.
    const auto n = static_cast<int>(s1.size());

    using FreqMap = std::array<int, 26>;
    std::array<FreqMap, 2> maps{};

    for (int i = 0; i < n; ++i) {
      ++maps[i & 1][s1[i] - 'a'];
      --maps[i & 1][s2[i] - 'a'];
    }

    return std::ranges::all_of(maps | std::views::join,
                               [](auto f) { return f == 0; });
  }
};
