#include <cstddef>
#include <string>
#include <vector>

class Solution {
 public:
  int compress(std::vector<char>& chars) {
    // s := ""
    // for each group of consecutive characters in chars:
    //   if group.length == 1:
    //     append c to s
    //   else:
    //     append c, followed by group.length
    // return s.length
    // MODIFY the input array and return its new length.
    int len = 0;  // represents the writeIdx
    int i = 0;
    while (i < chars.size()) {
      int repeats = 0;
      char curr = chars[i];

      while (i < chars.size() && chars[i] == curr) {
        ++i;
        ++repeats;
      }

      // modify the input array
      chars[len++] = curr;
      if (repeats > 1) {
        // repeats <= 2000
        // Can we do better than converting to a string?
        std::string digits = std::to_string(repeats);
        for (char d : digits) {
          chars[len++] = d;
        }
      }
    }

    return len;
  }
};
