#include <bitset>
#include <string_view>

class Solution {
 public:
  int numberOfSpecialChars(std::string_view word) {
    // A letter is special if it appears in both lower and upper case.
    // return the number of special letteres.
    std::bitset<26> lower{};
    std::bitset<26> upper{};
    for (auto c : word) {
      if (c >= 'a') {
        upper.set(c - 'a');
      } else {
        lower.set(c - 'A');
      }
    }

    return (lower & upper).count();
  }
};
