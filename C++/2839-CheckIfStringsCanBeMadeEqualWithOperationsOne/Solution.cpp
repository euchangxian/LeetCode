#include <algorithm>
#include <string>
#include <string_view>
#include <utility>

class Solution {
 public:
  bool canBeEqual(std::string s1, std::string s2) {
    // s1, s2 length 4, lowercase English letters.
    // Any number of times:
    // - Choose any two indices i and j, such that j-i = 2, swap characters.
    // Return true if s1 can be made equal to s2, false otherwise.
    //
    // Parity-based.
    // Set-equality.
    for (int i = 0; i < 2; ++i) {
      if (s1[i] > s1[i + 2]) {
        std::swap(s1[i], s1[i + 2]);
      }
      if (s2[i] > s2[i + 2]) {
        std::swap(s2[i], s2[i + 2]);
      }
    }

    return s1 == s2;
  }
};
