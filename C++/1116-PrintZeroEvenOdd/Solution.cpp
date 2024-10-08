#include <semaphore.h>

#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <semaphore>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class ZeroEvenOdd {
 private:
  int n;
  binary_semaphore semZero{1};
  binary_semaphore semOdd{0};
  binary_semaphore semEven{0};

 public:
  ZeroEvenOdd(int n) { this->n = n; }

  // printNumber(x) outputs "x", where x is an integer.
  void zero(function<void(int)> printNumber) {
    for (int i = 1; i <= n; ++i) {
      semZero.acquire();
      printNumber(0);
      if (i % 2) {
        semOdd.release();
      } else {
        semEven.release();
      }
    }
  }

  void even(function<void(int)> printNumber) {
    for (int i = 2; i <= n; i += 2) {
      semEven.acquire();
      printNumber(i);
      semZero.release();
    }
  }

  void odd(function<void(int)> printNumber) {
    for (int i = 1; i <= n; i += 2) {
      semOdd.acquire();
      printNumber(i);
      semZero.release();
    }
  }
};

void printNumber(int x) {
  cout << x;
}
