#include <algorithm>
#include <string>
#include <string_view>

class Solution {
 public:
  std::string processStr(std::string_view s) {
    // lowercase english letters,, special characters *, #, %.
    // Build result by processing left to right:
    // - if lowercase, append to result
    // - if *, remove the last character from result, if it exists
    // - if #, duplicate and append result to itself
    // - if %, reverse
    //
    // Simulation
    std::string result;
    result.reserve(1E5);
    for (auto c : s) {
      if (c == '*') {
        if (!result.empty()) {
          result.pop_back();
        }
      } else if (c == '#') {
        result += result;
      } else if (c == '%') {
        std::ranges::reverse(result);
      } else {
        result += c;
      }
    }

    return result;
  }
};
