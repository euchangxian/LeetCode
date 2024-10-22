#include <cstddef>
#include <deque>

using namespace std;
/**
 * Count the number of recent requests within a time frame.
 */
class RecentCounter {
 private:
  // Stores timestamps
  std::deque<int> window;

 public:
  RecentCounter() {}

  int ping(int t) {
    // bookkeeping
    while (!window.empty() && window.front() < t - 3000) {
      window.pop_front();
    }

    window.push_back(t);
    return static_cast<int>(window.size());
  }
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */
