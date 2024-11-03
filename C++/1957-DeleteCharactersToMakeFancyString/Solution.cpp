#include <cstddef>
#include <string>
#include <string_view>

using namespace std;
class Solution {
 public:
  string makeFancyString(std::string_view s) {
    // Fancy string is a string where no THREE consecutive characters are equal.
    // Just greedily add characters, unless there are already two consecutive
    // characters.
    std::string result;
    result.reserve(s.length());

    for (size_t i = 0; i < s.length(); ++i) {
      char curr = s[i];

      size_t resLen = result.length();
      if (resLen >= 2 && curr == result[resLen - 1] &&
          result[resLen - 1] == result[resLen - 2]) {
        continue;
      }
      result.push_back(curr);
    }
    return result;
  }
};