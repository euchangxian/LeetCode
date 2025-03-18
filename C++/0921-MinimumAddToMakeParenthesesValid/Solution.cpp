#include <cstddef>
#include <string>

class Solution {
 public:
  int minAddToMakeValid(std::string s) {
    // Unlike swapping, each add can only match 1 unmmatched bracket.
    int openBrackets = 0;
    int unmatched = 0;

    for (const char c : s) {
      if (c == '(') {
        ++openBrackets;
        continue;
      }

      if (openBrackets > 0) {
        --openBrackets;
      } else {
        ++unmatched;
      }
    }

    return unmatched + openBrackets;
  }
};
