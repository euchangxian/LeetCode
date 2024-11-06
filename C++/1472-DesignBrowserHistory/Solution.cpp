#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdlib>
#include <string>
#include <utility>

using namespace std;
/**
 * Able to move backwards/forward number of steps. I.e., history or a Stack.
 * visit clears the forward history.
 *
 * Use a vector that acts as a Stack. Increment and decrement the stack pointer
 * as appropriate.
 *
 * To clear the forward history, we can "resize" the vector. Though we probably
 * want to avoid reallocation by simply updating the "size" of the vector.
 */
class BrowserHistory {
 private:
  int stkPtr{};                             // points to the current URL
  int size{};                               // number of elements in the stack
  std::array<std::string, 5000> history{};  // at most 5000 calls

 public:
  // initialize with the homepage as the root
  BrowserHistory(std::string homepage)
      : stkPtr(0), size(1), history{{homepage}} {}

  void visit(std::string url) {
    history[++stkPtr] = std::move(url);
    size = stkPtr + 1;  // "resize"
  }

  std::string back(int steps) {
    // move the stack pointer down at most till 0.
    stkPtr = std::max(stkPtr - steps, 0);

    return history[stkPtr];
  }

  std::string forward(int steps) {
    // move the stack pointer up till at most size-1, the last element in the
    // stack.
    stkPtr = std::min(stkPtr + steps, size - 1);
    return history[stkPtr];
  }
};

/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */
