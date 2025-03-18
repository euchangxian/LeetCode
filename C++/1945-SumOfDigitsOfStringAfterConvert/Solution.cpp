#include <string>

class Solution {
 public:
  int getLucky(std::string s, int k) {
    std::string transformed;
    transformed.reserve(s.length());
    for (char c : s) {
      int digits = (c - 'a' + 1);

      transformed += std::to_string(digits);
    }

    while (k--) {
      int sum = 0;
      for (char c : transformed) {
        sum += c - '0';
      }
      transformed = std::to_string(sum);
    }
    return std::stoi(transformed);
  }
};
