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
 private:
  unordered_map<string, function<int(int, int)>> operations = {
      {"+", plus<>()},
      {"-", minus<>()},
      {"*", multiplies<>()},
      {"/", divides<>()}};

 public:
  int evalRPN(vector<string>& tokens) {
    stack<int> operands;

    for (string const& token : tokens) {
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
