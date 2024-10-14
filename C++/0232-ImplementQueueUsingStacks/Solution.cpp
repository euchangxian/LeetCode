#include <cstddef>
#include <stack>

using namespace std;
/**
 * FIFO(queue) using LIFO(stack).
 *
 * This means we need to keep the newest inserted element at the bottom of the
 * stack.
 *
 * Similar in concept to implementing LIFO (stack) using FIFO (queues).
 * Push exclusively to s1.
 * Pop exclusively from s2.
 */
class MyQueue {
 private:
  std::stack<int> s1;
  std::stack<int> s2;

 public:
  MyQueue() {}

  void push(int x) {
    // Reverses the order from FIFO to LIFO
    while (!s2.empty()) {
      s1.push(s2.top());
      s2.pop();
    }

    // Reverse the order again.
    s1.push(x);
    while (!s1.empty()) {
      s2.push(s1.top());
      s1.pop();
    }
  }

  int pop() {
    const int top = s2.top();
    s2.pop();
    return top;
  }

  int peek() { return s2.top(); }

  bool empty() { return s1.empty() && s2.empty(); }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
