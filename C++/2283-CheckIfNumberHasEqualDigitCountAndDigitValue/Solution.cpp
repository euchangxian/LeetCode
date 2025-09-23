#include <array>
#include <string_view>

class Solution {
 public:
  bool digitCount(std::string_view num) {
    // Return true if for every index i in the range 0<=i<n, the digit i occurs
    // num[i] times in num, otherwise return false.
    std::array<int, 10> freq{};
    for (char c : num) {
      ++freq[c - '0'];
    }

    for (int i = 0; i < num.size(); ++i) {
      if (freq[i] != num[i] - '0') {
        return false;
      }
    }
    return true;
  }
};
