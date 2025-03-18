#include <stack>
#include <vector>

class Solution {
 public:
  std::vector<int> dailyTemperatures(std::vector<int>& temperatures) {
    std::vector<int> result(temperatures.size(), 0);

    // Monotonically non-increasing stack
    std::stack<int> indices;
    for (int i = 0; i < temperatures.size(); ++i) {
      while (!indices.empty() &&
             temperatures[i] > temperatures[indices.top()]) {
        int top = indices.top();
        indices.pop();

        result[top] = i - top;
      }

      indices.push(i);
    }
    return result;
  }
};
