#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class Solution {
private:
  pair<int, int> expandCentre(const string &s, int left, int right) {
    while (left >= 0 && right < s.length() && s[left] == s[right]) {
      --left;
      ++right;
    }
    // Move left/right indices back to compensate for last iteration
    return {left + 1, right - 1};
  }

public:
  string longestPalindrome(string s) {
    int n = s.length();

    int start = 0;
    int maxLength = 1;
    for (int i = 0; i < n; ++i) {
      const auto &[oddL, oddR] = expandCentre(s, i, i);
      const auto &[evenL, evenR] = expandCentre(s, i, i + 1);

      if (oddR - oddL + 1 > maxLength) {
        start = oddL;
        maxLength = oddR - oddL + 1;
      }

      if (evenR - evenL + 1 > maxLength) {
        start = evenL;
        maxLength = evenR - evenL + 1;
      }
    }
    return s.substr(start, maxLength);
  }
};
