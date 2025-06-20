#include <algorithm>
#include <array>
#include <string_view>

class Solution {
 public:
  int maxDistance(std::string_view s, int k) {
    // s[i] = N|S|E|W, representing movement in an infinite grid.
    // Change at most k directions to get the maximum manhattan distance.
    //
    // Isnt this trivial? Oh. The maximum during the traversal.
    // Wew. Enumerate all possible combinations that result in maximum distance.
    // i.e., NW, NE, SW, SE
    const int n = s.size();
    int maxMD = 0;

    constexpr std::array<std::array<char, 2>, 4> dir{{
        {'N', 'W'},
        {'N', 'E'},
        {'S', 'W'},
        {'S', 'E'},
    }};

    for (auto keep : dir) {
      int delta = 0;
      int ops = 0;
      for (char c : s) {
        bool in = std::ranges::contains(keep, c);
        if (ops >= k && !in) {
          --delta;
          continue;
        }
        ops += !in;
        ++delta;
        maxMD = std::max(maxMD, delta);
      }
    }
    return maxMD;
  }
};
