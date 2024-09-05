#include <algorithm>
#include <climits>
#include <functional>
#include <future>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

void printFirst() { cout << "first"; }

void printSecond() { cout << "second"; }

void printThird() { cout << "third"; }

class Foo {
private:
  vector<promise<void>> promises;

public:
  Foo() : promises(3) {}

  void first(function<void()> printFirst) {

    // printFirst() outputs "first". Do not change or remove this line.
    printFirst();
    promises[1].set_value();
  }

  void second(function<void()> printSecond) {
    promises[1].get_future().wait();

    // printSecond() outputs "second". Do not change or remove this line.
    printSecond();

    promises[2].set_value();
  }

  void third(function<void()> printThird) {
    promises[2].get_future().wait();

    // printThird() outputs "third". Do not change or remove this line.
    printThird();
  }
};
