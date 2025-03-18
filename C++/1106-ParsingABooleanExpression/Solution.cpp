#include <cassert>
#include <cstddef>
#include <functional>
#include <string_view>

class Solution {
 public:
  bool parseBoolExpr(std::string_view expression) {
    // 't' evaluates to true
    // 'f' evaluates to false
    // "!(expression)" evaluates to logical NOT
    // "&(expression...)" evaluates to logical AND
    // "|(expression...)" evaluates to logical OR
    // Seems similar to 394 - Decode String
    // Seems like if expression is length 1, it must be a plain 't' or
    // 'f'. The next possible expression would be something like "!(t)",
    // which is of length 4. Then !(&(t,t)) => length 9. There cant be
    // something like (t, t), where there is no boolean operator.
    int idx = 0;
    return parseExpr(expression, idx);
  }

 private:
  bool evaluate(std::string_view expression,
                int& idx,
                bool init,
                std::function<bool(bool, bool)> op) {
    ++idx;  // skip '('
    while (idx < expression.length() && expression[idx] != ')') {
      // The first token in a bracket will not be a comma.
      bool subExpr = parseExpr(expression, idx);
      init = op(init, subExpr);

      if (expression[idx] == ')') {
        // end of subexpression. Another check is required here, because
        // parseExpr increased idx.
        // This is for e.g. !(&(...), ...) where the closing parentheses is
        // followed by a comma, resulting in wrong evaluation.
        break;
      }
      ++idx;  // skip ','
    }
    ++idx;  // skip ')'
    return init;
  }

  bool parseExpr(std::string_view expression, int& idx) {
    const char token = expression[idx++];
    switch (token) {
      case 't':
        return true;
      case 'f':
        return false;
      case '!':
        return evaluate(expression, idx, false,
                        [](bool init, bool subExpr) { return !subExpr; });
      case '&':
        return evaluate(expression, idx, true,
                        [](bool init, bool subExpr) { return init & subExpr; });
      case '|':
        return evaluate(expression, idx, false,
                        [](bool init, bool subExpr) { return init | subExpr; });
    }

    // should not reach here. Indicates invalid input
    assert("invalid input");
    return false;
  }
};
