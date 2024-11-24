#include <array>
#include <cstddef>
#include <cstdlib>
#include <string>

class Solution {
 public:
  std::string intToRoman(int num) {
    // With a little special cases like "IV" = 4, "IX" = 9, "XL" = 40, etc which
    // are subtractive forms. Only 4, 9, 40, 90, 400, 900 are used.
    //
    // If value does not start with 4 or 9, select the symbol with the maximal
    // value.
    // If the value starts with 4 or 9, use the subtractive form.
    std::array<int, 13> valueThresholds{{
        1000,
        900,
        500,
        400,
        100,
        90,
        50,
        40,
        10,
        9,
        5,
        4,
        1,
    }};

    std::array<std::string, 13> symbols{{
        "M",
        "CM",
        "D",
        "CD",
        "C",
        "XC",
        "L",
        "XL",
        "X",
        "IX",
        "V",
        "IV",
        "I",
    }};

    std::string roman;
    roman.reserve(64);  // random number i guess.
    for (int i = 0; i < valueThresholds.size() && num > 0; ++i) {
      while (valueThresholds[i] <= num) {
        num -= valueThresholds[i];
        roman += symbols[i];
      }
    }
    return roman;
  }
};
