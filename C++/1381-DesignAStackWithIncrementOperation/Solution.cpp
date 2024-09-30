#include <cstddef>
#include <vector>

using std::vector;
class CustomStack {
private:
  // Stack
  vector<int> stack;

  // Lazily propagated increments
  vector<int> incr;

  // Stack pointer
  size_t sp;

  // Capacity of the stack
  const size_t maxSize;

public:
  CustomStack(int maxSize)
      : stack(maxSize), incr(maxSize, 0), sp(0), maxSize(maxSize) {}

  void push(int x) {
    if (isFull()) {
      return;
    }
    stack[sp++] = x;
  }

  int pop() {
    if (isEmpty()) {
      return -1;
    }

    // When popping, the increment needs to be propagated.
    // Exploits the property that the increments are monotonic, where if the
    // kth element has an increment, then the k-1th element must also have
    // the same or more increment.
    --sp;
    const int popped = stack[sp] + incr[sp];

    if (!isEmpty()) {
      incr[sp - 1] += incr[sp];
    }

    // book-keeping for incr
    incr[sp] = 0;
    return popped;
  }

  void increment(int k, int val) {
    if (isEmpty() || k == 0) {
      return;
    }
    incr[std::min(static_cast<size_t>(k), sp) - 1] += val;
  }

  inline bool isFull() const noexcept { return sp >= maxSize; }

  inline bool isEmpty() const noexcept { return sp == 0; }
};

/**
 * Your CustomStack object will be instantiated and called as such:
 * CustomStack* obj = new CustomStack(maxSize);
 * obj->push(x);
 * int param_2 = obj->pop();
 * obj->increment(k,val);
 */
