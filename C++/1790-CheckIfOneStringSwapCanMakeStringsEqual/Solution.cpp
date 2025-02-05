#include <cstddef>
#include <cstdlib>
#include <string_view>

class Solution {
 public:
  bool areAlmostEqual(std::string_view s1, std::string_view s2) {
    // Swap characters at (i, j) once to make s1 == s2.
    // Find two positions that s1 and s2 are different. if s1[i] == s2[j] and
    // s1[j] == s2[i], then return true.
    // Otherwise, return false (if there are more than two differing positions,
    // or the swap would not make equal strings).
    const int n = s1.size();

    int i = -1;
    int j = -1;
    for (int k = 0; k < n; ++k) {
      if (s1[k] == s2[k]) {
        continue;
      }

      if (i == -1) {
        // if first differing not found
        i = k;
      } else if (j == -1) {
        // if first differing is found, and second is not yet found
        j = k;
      } else {
        // if two differing positions has already been found
        return false;
      }
    }

    if (i == -1 && j == -1) {
      return true;  // both equal
    }

    return (i != -1 && j != -1) && (s1[i] == s2[j] && s1[j] == s2[i]);
  }
};
