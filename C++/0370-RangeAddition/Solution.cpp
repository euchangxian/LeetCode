#include <array>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  std::vector<int> getModifiedArray(int length,
                                    std::vector<std::vector<int>>& updates) {
    // updates[i] = [startIdx, endIdx, incr]
    // array of specified length initially all 0.
    // increment elements within the range [start, end] inclusive by incr.
    //
    // Wew, segment trees? BITs? Related to prefixes. Line Sweep...
    std::array<int, 100'002> events{};
    for (const auto& update : updates) {
      const int startIdx = update[0];
      const int endIdx = update[1];
      const int incr = update[2];

      events[startIdx] += incr;
      events[endIdx + 1] -= incr;
    }

    int sum = 0;
    std::vector<int> arr(length, 0);

    for (int i = 0; i < length; ++i) {
      sum += events[i];
      arr[i] = sum;
    }
    return arr;
  }
};
