#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class Solution {
public:
  string convert(string s, int numRows) {
    if (numRows < 2) {
      return s;
    }

    // C++ strings are mutable. No need for StringBuilder equivalent
    vector<string> rowStrings(numRows, "");

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

    string result;
    for (const auto &str : rowStrings) {
      result += str;
    }

    return result;
  }
};
