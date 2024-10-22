#include <cstddef>
#include <deque>

using namespace std;
class MovingAverage {
  const size_t capacity;

  double windowSum;
  std::deque<int> window;

 public:
  MovingAverage(int size) : capacity(size), windowSum(0) {}

  double next(int val) {
    // Remove the left of the window, if necessary
    if (window.size() >= capacity) {
      windowSum -= window.front();
      window.pop_front();
    }
    window.push_back(val);
    windowSum += val;

    return windowSum / window.size();
  }
};

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage* obj = new MovingAverage(size);
 * double param_1 = obj->next(val);
 */
