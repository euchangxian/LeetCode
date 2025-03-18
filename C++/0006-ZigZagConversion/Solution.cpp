#include <string>
#include <vector>

class Solution {
 public:
  std::string convert(std::string s, int numRows) {
    if (numRows < 2) {
      return s;
    }

    // C++ strings are mutable. No need for StringBuilder equivalent
    std::vector<std::string> rowStrings(numRows, "");

    int i = 0;
    while (i < s.length()) {
      // Vertically Down
      for (int j = 0; j < numRows && i < s.length(); ++j) {
        rowStrings[j] += s[i++];
      }

      // Diagonally Up
      // Little bit tricky indexing, where the first and last row do not
      // have characters
      for (int j = numRows - 2; j >= 1 && i < s.length(); --j) {
        rowStrings[j] += s[i++];
      }
    }

    std::string result;
    for (const auto& str : rowStrings) {
      result += str;
    }

    return result;
  }
};
