#include <vector>

class Solution {
 public:
  bool isOneBitCharacter(std::vector<int>& bits) {
    // Two special characters:
    // - first character can be represented by one bit 0.
    // - second character can be represented by two bits (10 or 11)
    // Given a binary array bits, return true if the last character must be
    // a one-bit character.
    const auto n = static_cast<int>(bits.size());

    int i = 0;
    while (i < n - 1) {
      if (bits[i] == 1) {
        ++i;
      }
      ++i;
    }

    if (i >= n || bits[n - 1] == 1) {
      return false;
    }

    return true;
  }
};
