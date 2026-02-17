#include <format>
#include <string>
#include <vector>

class Solution {
 public:
  std::vector<std::string> readBinaryWatch(int turnedOn) {
    // 4 LEDs on the top to represent hours, 6 LEDs on the bottom to represent
    // minutes.
    // Each LED represents a 0 or 1, with the LSB on the right.
    // turnedOn represents the number of LEDs on.
    // Return all possible times the watch could represent.
    // Hour must not contain a leading zero.
    //
    // Let the higher 4 bits represent the hours, lower 6 bits represent
    // minutes.
    constexpr auto BITS = 10;
    constexpr auto MINUTES = 6;
    constexpr auto MINUTES_MASK = (1 << MINUTES) - 1;

    std::vector<std::string> result;
    for (int i = 0; i < (1 << BITS); ++i) {
      if (__builtin_popcount(i) != turnedOn) {
        continue;
      }

      auto h = i >> MINUTES;
      auto m = i & MINUTES_MASK;
      if (h >= 12 || m >= 60) {
        continue;
      }

      result.emplace_back(std::format("{}:{}", std::to_string(h),
                                      (m < 10 ? "0" : "") + std::to_string(m)));
    }
    return result;
  }
};
