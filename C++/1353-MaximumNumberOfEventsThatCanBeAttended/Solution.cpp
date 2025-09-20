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

class Solution {
 public:
  int maxEvents(std::vector<std::vector<int>>& events) {
    // events[i] = [startDay, endDay) (can start on an end day)
    // You can attend event i at any day d where startTime <= d <= endTime.
    // Can only attend one event at any time d.
    // Return the maximum number of events that can be attended.
    //
    // Sort by start.
    // Greedily pick the shortest duration using a heap.
    auto n = static_cast<int>(events.size());
    std::ranges::sort(events);

    int result = 0;
    std::priority_queue<int, std::vector<int>, std::greater<>> pq;
    for (const auto& e : events) {
      while (!pq.empty() && pq.top()) {
      }
    }
    return result;
  }
};
