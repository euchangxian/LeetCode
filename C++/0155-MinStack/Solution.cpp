#include <climits>
#include <cstddef>
#include <stack>

/**
 * At first glance, seemed like keeping track of the minimum element would
 * suffice. But what if the minimum element is popped? How would the next
 * minimum element be determined?
 *
 * Therefore, we need to keep track of the minimum element of the first i
 * elements.
 * A separate stack can be used.
 */
class MinStack {
 private:
  std::stack<int> stk;
  std::stack<int> minStk;

 public:
  MinStack() {}

  void push(int val) {
    stk.push(val);

    const int currMin = minStk.empty() ? INT_MAX : minStk.top();
    minStk.push(std::min(currMin, val));
  }

  void pop() {
    stk.pop();
    minStk.pop();
  }

  int top() {
    // No need to check for non-empty due to problem constraints
    return stk.top();
  }

  int getMin() {
    // Similarly, no need to check.
    return minStk.top();
  }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
