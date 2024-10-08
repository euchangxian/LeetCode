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
  vector<int> dailyTemperatures(vector<int>& temperatures) {
    vector<int> result(temperatures.size(), 0);

    // Monotonically non-increasing stack
    stack<int> indices;
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
