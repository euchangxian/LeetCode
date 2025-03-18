#include <string>

class Solution {
 public:
  // score of a string is defined as the SUM of the absolute difference between
  // the ASCII values of adjacent characters.
  int scoreOfString(std::string s) {
    if (s.length() < 2) {
      return 0;
    }

    int score = 0;
    for (int i = 1; i < s.length(); ++i) {
      score += std::abs(s[i] - s[i - 1]);
    }
    return score;
  }
};
