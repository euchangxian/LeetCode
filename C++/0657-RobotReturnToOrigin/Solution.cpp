#include <string_view>

class Solution {
 public:
  bool judgeCircle(std::string_view moves) {
    // Start at (0, 0).
    // Given a sequence of move, return true if the robot ends at (0, 0).
    // moves[i] = R|L|U|D

    int deltaVertical = 0;
    int deltaHorizontal = 0;

    for (auto m : moves) {
      if (m == 'R') {
        ++deltaHorizontal;
      } else if (m == 'L') {
        --deltaHorizontal;
      } else if (m == 'U') {
        ++deltaVertical;
      } else {
        --deltaVertical;
      }
    }

    return deltaVertical == 0 && deltaHorizontal == 0;
  }
};
