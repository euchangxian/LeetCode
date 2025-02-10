#include <cstddef>
#include <cstdlib>
#include <string>
#include <string_view>

class Solution {
 public:
  std::string clearDigits(std::string_view s) {
    // delete first, and closest non-digit to the left.
    std::string result;
    result.reserve(s.size());
    for (char c : s) {
      if (std::isalpha(c)) {
        result += c;
      } else {
        result.pop_back();
      }
    }
    return result;
  }
};
