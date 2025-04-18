#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstdint>
#include <deque>
#include <functional>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// Infinite stacks arranged in a row, each with the same capacity.
// While infinite, the index is only up to 10^5. Lol. Effectively finite for
// all intents and purpose.
//
// Suppose index is really infinite, but the number of calls to popAtStack is
// bounded.
// Augmented with a std::set for the non-capacity list, and non-empty list.
constexpr int MAX_N = 2 * 1e5;
class DinnerPlates {
 public:
  DinnerPlates(int capacity) : capacity(capacity), lazy(0), row{} {
    notcapacity.insert(lazy++);
  }

  void push(int val) {
    if (notcapacity.empty()) {
      if (lazy + 1 <= MAX_N) {
        notcapacity.insert(lazy++);
      } else {
        return;  // doesnt really abide by "infinite"
      }
    }

    int idx = *notcapacity.begin();
    row[idx].push(val);

    if (!nonempty.contains(idx)) {
      nonempty.insert(idx);
    }

    if (row[idx].size() >= capacity) {
      notcapacity.erase(idx);
    }
  }

  int pop() {
    if (nonempty.empty()) {
      return -1;
    }

    // rightmost
    int idx = *nonempty.rbegin();
    int val = row[idx].top();
    row[idx].pop();

    if (row[idx].empty()) {
      nonempty.erase(idx);
    }

    if (!notcapacity.contains(idx)) {
      notcapacity.insert(idx);
    }
    return val;
  }

  int popAtStack(int index) {
    if (row[index].empty()) {
      return -1;
    }

    int val = row[index].top();
    row[index].pop();

    if (row[index].empty()) {
      nonempty.erase(index);
    }

    if (!notcapacity.contains(index)) {
      notcapacity.insert(index);
    }
    return val;
  }

 private:
  int capacity;
  int lazy;  // instead of eagerly pushing all empty stacks to notcapacity

  std::array<std::stack<int>, MAX_N + 1> row{};
  std::set<int> notcapacity;
  std::set<int> nonempty;
};

/**
 * Your DinnerPlates object will be instantiated and called as such:
 * DinnerPlates* obj = new DinnerPlates(capacity);
 * obj->push(val);
 * int param_2 = obj->pop();
 * int param_3 = obj->popAtStack(index);
 */
