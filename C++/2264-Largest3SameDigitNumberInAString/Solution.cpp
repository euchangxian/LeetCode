#include <algorithm>
#include <string>
#include <string_view>

class Solution {
 public:
  std::string largestGoodInteger(std::string_view num) {
    // Given string num representing a large integer.
    // An integer is good if:
    // - it is a substring of num with length 3,
    // - consist of only one unique digit.
    // Return the maximum good integer as a string, empty if none exists.
    auto n = static_cast<int>(num.size());

    int result = -1;
    for (int i = 1; i < n - 1; ++i) {
      if (num[i - 1] == num[i] && num[i] == num[i + 1]) {
        result = std::max(result, num[i] - '0');
      }
    }

    return result == -1 ? "" : std::string(3, result + '0');
  }
};
