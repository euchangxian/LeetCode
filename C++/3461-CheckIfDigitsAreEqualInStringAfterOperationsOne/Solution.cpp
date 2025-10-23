#include <string>

class Solution {
 public:
  bool hasSameDigits(std::string s) {
    // Repeat until s.length == 2
    // - For each pair of consecutive digits starting from the first, calculate
    //   a new digit modulo 10.
    // - Replace.
    // Return true if the final 2 digits are equal.
    //
    // Seems like the Pascal's Triangle again, where each digit is included in
    // the final modulo sum f times.
    // Simulation-wise: Each operation removes 1 from the string. Repeat n-2
    // times.
    const auto n = static_cast<int>(s.size());
    for (int i = 0; i < n - 2; ++i) {
      for (int j = 0; j < n - i - 1; ++j) {
        s[j] = ((s[j] - '0' + s[j + 1] - '0') % 10) + '0';
      }
    }

    return s[0] == s[1];
  }
};
