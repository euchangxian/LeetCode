#include <semaphore.h>

#include <functional>
#include <iostream>
#include <semaphore>

class ZeroEvenOdd {
 private:
  int n;
  std::binary_semaphore semZero{1};
  std::binary_semaphore semOdd{0};
  std::binary_semaphore semEven{0};

 public:
  ZeroEvenOdd(int n) { this->n = n; }

  // printNumber(x) outputs "x", where x is an integer.
  void zero(std::function<void(int)> printNumber) {
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

  void even(std::function<void(int)> printNumber) {
    for (int i = 2; i <= n; i += 2) {
      semEven.acquire();
      printNumber(i);
      semZero.release();
    }
  }

  void odd(std::function<void(int)> printNumber) {
    for (int i = 1; i <= n; i += 2) {
      semOdd.acquire();
      printNumber(i);
      semZero.release();
    }
  }
};

void printNumber(int x) {
  std::cout << x;
}
