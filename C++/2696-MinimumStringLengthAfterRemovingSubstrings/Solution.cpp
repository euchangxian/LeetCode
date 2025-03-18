#include <stack>
#include <string>

class Solution {
 public:
  int minLength(std::string s) {
    std::stack<char> stk;
    for (char c : s) {
      const bool isPrevA = !stk.empty() && stk.top() == 'A';
      const bool isPrevC = !stk.empty() && stk.top() == 'C';
      if (c == 'B' && isPrevA || c == 'D' && isPrevC) {
        stk.pop();
        continue;
      }

      stk.push(c);
    }
    return stk.size();
  }
};
