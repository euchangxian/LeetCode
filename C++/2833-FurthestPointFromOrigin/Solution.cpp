#include <cmath>
#include <string_view>

class Solution {
 public:
  int furthestDistanceFromOrigin(std::string_view moves) {
    // moves, length n.
    // moves[i] = L|R|_ representing left, right, either movement on a number
    // line starting from 0.
    // Return the distance from the origin of the furthest point after n moves.
    auto delta = 0;
    auto wildcard = 0;
    for (auto c : moves) {
      if (c == 'L') {
        --delta;
      } else if (c == 'R') {
        ++delta;
      } else {
        ++wildcard;
      }
    }
    return std::abs(delta) + wildcard;
  }
};
