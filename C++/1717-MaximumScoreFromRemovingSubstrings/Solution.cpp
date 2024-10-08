#include <string>

using namespace std;
class Solution {
 public:
  int maximumGain(string s, int x, int y) {
    char currentTarget = 'b';
    char topTarget = 'a';
    int points = x;

    // Look for "ba" first, since y is higher
    if (y > x) {
      currentTarget = 'a';
      topTarget = 'b';
      points = y;
    }

    int result = 0;
    string remaining;
    for (char c : s) {
      if (c == currentTarget && !remaining.empty() &&
          remaining.back() == topTarget) {
        remaining.pop_back();
        result += points;
        continue;
      }
      remaining += c;
    }

    s = remaining;
    remaining.clear();

    char temp = currentTarget;
    currentTarget = topTarget;
    topTarget = temp;
    if (points == x) {
      points = y;
    } else {
      points = x;
    }

    for (char c : s) {
      if (c == currentTarget && !remaining.empty() &&
          remaining.back() == topTarget) {
        remaining.pop_back();
        result += points;
        continue;
      }
      remaining += c;
    }

    return result;
  }
};
