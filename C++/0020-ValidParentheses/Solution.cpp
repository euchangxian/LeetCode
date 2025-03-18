#include <stack>
#include <string>

class Solution {
 public:
  bool isValid(std::string s) {
    std::stack<char> expected;

    for (char const& c : s) {
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
