#include <array>
#include <stack>
#include <string>

class Solution {
 public:
  std::string clearStars(std::string s) {
    // Given string s of lowercase characters, which may contain '*'.
    // While there is a '*',
    // - Delete the leftmost '*' and the smallest non-'*' character to its left.
    //   If there are multiple candidates, delete any.
    // Thus, we want to delete the rightmost smallest greedily.
    std::array<std::stack<int>, 26> prefix;
    for (int i = 0; i < s.size(); ++i) {
      if (s[i] != '*') {
        prefix[s[i] - 'a'].push(i);
        continue;
      }

      for (auto& stk : prefix) {
        if (!stk.empty()) {
          int idx = stk.top();
          stk.pop();
          s[idx] = '*';
          break;
        }
      }
    }

    std::string result;
    result.reserve(s.size());
    for (char c : s) {
      if (c != '*') {
        result += c;
      }
    }
    return result;
  }
};
