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
public:
  bool isValid(string s) {
    stack<char> expected;

    for (char const &c : s) {
      if (c == '(') {
        expected.push(')');
        continue;
      }
      if (c == '{') {
        expected.push('}');
        continue;
      }
      if (c == '[') {
        expected.push(']');
        continue;
      }

      if (expected.empty()) {
        return false;
      }

      char prev = expected.top();
      expected.pop();
      if (prev != c) {
        return false;
      }
    }

    return expected.empty();
  }
};
