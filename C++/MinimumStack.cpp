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
class MinStack {
private:
  stack<int> stk;
  stack<int> minStack;

public:
  MinStack() {}

  void push(int val) {
    stk.push(val);
    if (!minStack.empty()) {
      minStack.push(min(val, minStack.top()));
    } else {
      minStack.push(val);
    }
  }

  void pop() {
    stk.pop();
    minStack.pop();
  }

  int top() { return stk.top(); }

  int getMin() { return minStack.top(); }
};
