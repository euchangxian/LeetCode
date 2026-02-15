#include <algorithm>
#include <string>
#include <string_view>

class Solution {
 public:
  std::string addBinary(std::string_view a, std::string_view b) {
    // Given two binary strings, return their sum as a binary string.
    //
    // For the linked list approach, it involves recursing to the end, and
    // bringing the carry forward.
    // If it reaches the head, then we add a node to the front.
    // Though, for strings, it's an O(N) operation.
    // Hm.
    const auto m = static_cast<int>(a.size());
    const auto n = static_cast<int>(b.size());

    std::string result;
    result.reserve(std::max(m, n));
    int carry = 0;
    for (int i = m - 1, j = n - 1; i >= 0 || j >= 0 || carry >= 1;) {
      if (i >= 0) {
        carry += a[i--] - '0';
      }
      if (j >= 0) {
        carry += b[j--] - '0';
      }

      result += (carry % 2) + '0';
      carry /= 2;
    }
    std::ranges::reverse(result);
    return result;
  }
};
