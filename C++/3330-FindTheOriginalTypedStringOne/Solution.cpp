#include <string_view>

class Solution {
 public:
  int possibleStringCount(std::string_view word) {
    // At most one character was typed multiple times.
    // Return the number of possible original strings.
    // Each sequence of characters (2 or more) represents a possible mistype,
    // where, a sequence of length 1 still represents a possible original, given
    // that its at most once.
    auto n = static_cast<int>(word.size());

    // no mistype.
    int result = 1;

    int i = 0;
    while (i < n) {
      char curr = word[i];
      int count = 0;
      while (i < n && word[i] == curr) {
        ++i;
        ++count;
      }
      result += count - 1;
    }
    return result;
  }
};
