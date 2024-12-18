#include <array>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  bool isCovered(std::vector<std::vector<int>>& ranges, int left, int right) {
    // ranges[i] = [start, end] inclusive.
    // Return True if each integer in the inclusive range [left, right] is
    // covered by at least one range.
    // False otherwise.
    // x is covered if start <= x <= end.
    std::array<int, 52> points{};
    for (const auto& range : ranges) {
      ++points[range[0]];
      --points[range[1] + 1];
    }

    int sum = 0;
    for (int i = 0; i < points.size(); ++i) {
      sum += points[i];

      if (sum == 0 && left <= i && i <= right) {
        return false;
      }
    }
    return true;
  }
};
