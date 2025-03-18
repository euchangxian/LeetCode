#include <functional>
#include <future>
#include <iostream>
#include <vector>

void printFirst() {
  std::cout << "first";
}

void printSecond() {
  std::cout << "second";
}

void printThird() {
  std::cout << "third";
}

class Foo {
 public:
  Foo() : promises(3) {}

  void first(std::function<void()> printFirst) {
    // printFirst() outputs "first". Do not change or remove this line.
    printFirst();
    promises[1].set_value();
  }

  void second(std::function<void()> printSecond) {
    promises[1].get_future().wait();

    // printSecond() outputs "second". Do not change or remove this line.
    printSecond();

    promises[2].set_value();
  }

  void third(std::function<void()> printThird) {
    promises[2].get_future().wait();

    // printThird() outputs "third". Do not change or remove this line.
    printThird();
  }

 private:
  std::vector<std::promise<void>> promises;
};
