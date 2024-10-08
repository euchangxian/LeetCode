#include <string>

using namespace std;
class Solution {
 public:
  // score of a string is defined as the SUM of the absolute difference between
  // the ASCII values of adjacent characters.
  int scoreOfString(string s) {
    if (s.length() < 2) {
      return 0;
    }

    int score = 0;
    for (int i = 1; i < s.length(); ++i) {
      score += abs(s[i] - s[i - 1]);
    }
    return score;
  }
};
