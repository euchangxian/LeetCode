#include <algorithm>
#include <cstddef>
#include <queue>

using namespace std;
/**
 * Use two Queues (FIFO) to implement a Stack (LIFO).
 * The idea is to exploit amortization.
 * When pushing to the queue, push only to queue1.
 * The newly pushed element will be the top of the abstract stack.
 * Thus, for any existing elements in queue2, pop and push to queue1,
 * maintaining the LIFO order of queue1.
 *
 * Finally, swap q1 and q2. This allows us to keep q1 empty, popping only from
 * q2.
 */
class MyStack {
 private:
  std::queue<int> q1;
  std::queue<int> q2;

 public:
  MyStack() {}

  void push(int x) {
    q1.push(x);

    while (!q2.empty()) {
      q1.push(q2.front());
      q2.pop();
    }

    swap(q1, q2);
  }

  int pop() {
    const int top = q2.front();
    q2.pop();
    return top;
  }

  int top() { return q2.front(); }

  bool empty() { return q1.empty() && q2.empty(); }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
