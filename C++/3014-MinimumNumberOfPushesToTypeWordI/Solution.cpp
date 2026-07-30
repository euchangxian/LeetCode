#include <string_view>

class Solution {
 public:
  int minimumPushes(std::string_view word) {
    // Distinct lower case letters.
    // Remap letters on the phone pad.
    // Return minimum number of pushes.
    //
    // maintain cursor
    const auto n = static_cast<int>(word.size());
    auto result = 0;
    for (auto i = 0; i < n; ++i) {
      result += i / 8 + 1;
    }
    return result;
  }
};
