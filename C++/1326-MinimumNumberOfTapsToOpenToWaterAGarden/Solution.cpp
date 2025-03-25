#include <algorithm>
#include <array>
#include <utility>
#include <vector>

constexpr int MAX_N = 1e4;
class Solution {
 public:
  int minTaps(int n, std::vector<int>& ranges) {
    // n+1 taps such that ranges[i] means the ith tap can water the area
    // [i - ranges[i], i + ranges[i]] if it was open.
    // Water the whole garden of length n.
    //
    // First intuitive step would be to reduce this to an interval problem:
    // ranges[i] = [i-ranges[i], i+ranges[i]]
    // Then, we want the minimum number of intervals such that the entire range
    // [0..n] (yes. inclusive n) is covered.
    std::array<int, MAX_N + 1> line{};
    for (int i = 0; i < ranges.size(); ++i) {
      // clamp the interval
      int left = std::max(0, i - ranges[i]);
      int right = std::min(n, i + ranges[i]);

      // Take the best interval.
      line[left] = std::max(line[left], right);
    }

    int currEnd = line[0];
    int nextEnd = 0;  // save the end of next best tap.
    int result = 1;

    // if the current best tap can cover the entire range, i.e., currEnd >= n
    // then break early to avoid overcounting
    for (int x = 1; x <= n && currEnd < n; ++x) {
      if (x > currEnd) {
        return -1;  // not possible to cover.
      }

      nextEnd = std::max(nextEnd, line[x]);
      if (x == currEnd) {
        ++result;
        currEnd = std::exchange(nextEnd, 0);
      }
    }
    return result;
  }
};
