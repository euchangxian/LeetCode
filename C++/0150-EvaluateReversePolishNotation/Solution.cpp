#include <functional>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

class Solution {
 private:
  std::unordered_map<std::string, std::function<int(int, int)>> operations = {
      {"+", std::plus<>()},
      {"-", std::minus<>()},
      {"*", std::multiplies<>()},
      {"/", std::divides<>()}};

 public:
  int evalRPN(std::vector<std::string>& tokens) {
    std::stack<int> operands;

    for (const std::string& token : tokens) {
      if (operations.count(token)) {
        // Qn constraint means the equation is valid
        int op2 = operands.top();
        operands.pop();
        int op1 = operands.top();
        operands.pop();

        int result = operations[token](op1, op2);
        operands.push(result);
        continue;
      }

      operands.push(stoi(token));
    }
    return operands.top();
  }
};
