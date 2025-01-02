#include <cstddef>
#include <cstdlib>
#include <string>
#include <string_view>
#include <vector>

class Solution {
 public:
  std::string stringShift(std::string_view s,
                          std::vector<std::vector<int>>& shift) {
    // shift[i] = [direction, amount]
    // direction = 0 (left) | 1 (right)
    // left shift by 1 => remove first character of s, append to the right.
    // right shift by 1 => remove last character of s, prepend to the left
    // Simulation works given the constraints.
    // Can do better by aggregating the final shift.
    int rightShifts = 0;  // negative for left, positive for right.
    for (const auto& sh : shift) {
      if (sh[0] == 0) {
        rightShifts -= sh[1];
      } else {
        rightShifts += sh[1];
      }
    }

    if (rightShifts == 0) {
      return std::string(s.begin(), s.end());
    }

    const int n = static_cast<int>(s.size());
    rightShifts = ((rightShifts % n) + n) % n;

    std::string result;
    result.reserve(s.size());

    // Right shift by k: take s[n-k:] and append s[:n-k]
    int k = n - rightShifts;
    result.append(s.substr(k));
    result.append(s.substr(0, k));
    return result;
  }
};
