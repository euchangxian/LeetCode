#include <algorithm>
#include <functional>
#include <unordered_map>
#include <vector>

class Solution {
 public:
  int maxNumberOfFamilies(int n, std::vector<std::vector<int>>& reservedSeats) {
    // n rows, 10 cols.
    // 1 2 3 _ 4 5 6 7 _ 8 9 10
    // valid windows: [2345], [4567], [6789].
    // Reserved/taken seats - window not valid.
    // Return maximum number of windows.
    //
    // n <= 1E9
    // 1 <= reservedSeats.length <= min(1E4, n*10)
    constexpr auto LEFT_MASK =
        (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5);  // cols 2,3,4,5
    constexpr auto RIGHT_MASK =
        (1 << 6) | (1 << 7) | (1 << 8) | (1 << 9);  // cols 6,7,8,9
    constexpr auto MID_MASK =
        (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7);  // cols 4,5,6,7

    std::unordered_map<int, int> occupied;
    occupied.reserve(reservedSeats.size());
    for (const auto& seat : reservedSeats) {
      auto row = seat[0];
      auto col = seat[1];

      if (col >= 2 && col <= 9) {
        occupied[row] |= (1 << col);
      }
    }

    // rows with no occupancy can be assigned optimally x2.
    auto result = (n - static_cast<int>(occupied.size())) * 2;
    for (const auto& [_, rowMask] : occupied) {
      auto canAssignLeft = (rowMask & LEFT_MASK) == 0;
      auto canAssignRight = (rowMask & RIGHT_MASK) == 0;
      auto canAssignMiddle = (rowMask & MID_MASK) == 0;

      if (canAssignLeft && canAssignRight) {
        result += 2;
        continue;
      }

      result += (canAssignLeft | canAssignMiddle | canAssignRight);
    }
    return result;
  }
};
