#include <array>
#include <deque>
#include <utility>

// Counts the number of hits received in the past 5 minutes (300 seconds)
// Calls are made to the HitCounter in chronological order.
constexpr int WINDOW_SIZE = 300;
class HitCounter {
private:
  std::array<int, WINDOW_SIZE> hits;
  std::array<int, WINDOW_SIZE> time;

public:
  // Value initialize
  HitCounter() : hits{}, time{} {}

  void hit(const int timestamp) {
    const int idx = timestamp % WINDOW_SIZE;
    if (time[idx] < timestamp) {
      time[idx] = timestamp;
      hits[idx] = 0;
    }
    ++hits[idx];
  }

  int getHits(const int timestamp) {
    int total{0};

    for (int i = 0; i < WINDOW_SIZE; ++i) {
      total += hits[i] * (timestamp - time[i] < 300);
    }
    return total;
  }
};

class HitCounterNaive {
private:
  // Stores {timestamp, hits}
  std::deque<std::pair<int, int>> hits;

  int runningHits;

public:
  HitCounterNaive() : runningHits(0) {}

  void hit(int timestamp) {
    if (hits.empty() || hits.back().first < timestamp) {
      hits.emplace_back(timestamp, 0);
    }
    ++hits.back().second;
    ++runningHits;
    return;
  }

  int getHits(int timestamp) {
    // Remove nodes that do not fit in the window
    while (!hits.empty() && timestamp - hits.front().first >= 300) {
      runningHits -= hits.front().second;
      hits.pop_front();
    }

    return runningHits;
  }
};

/**
 * Your HitCounter object will be instantiated and called as such:
 * HitCounter* obj = new HitCounter();
 * obj->hit(timestamp);
 * int param_2 = obj->getHits(timestamp);
 */
