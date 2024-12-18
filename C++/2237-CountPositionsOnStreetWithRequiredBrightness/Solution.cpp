#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  int meetRequirement(int n,
                      std::vector<std::vector<int>>& lights,
                      std::vector<int>& requirement) {
    // line from 0 to n-1.
    // lights[i] = [position, range], indicating a lamp at position that
    // illuminates the area from position-range to position+range, clamped
    // within 0 to n-1.
    // Brighness of a point is the number of lamps that light up the position.
    // Want: number of positions i that have a brightness of at least
    // requirement[i]
    // prefix sum / Line Sweep.
    // The difficulty seems to be determining which points (that are implicitly
    // illuminated) meet the requirement.
    // Given the input size of n <= 10^5, we can probably fit all points into
    // a fixed size array/vector which simplifies things.
    std::array<int, 100'002> points{};
    for (const auto& light : lights) {
      const int position = light[0];
      const int range = light[1];

      const int start = std::max(0, position - range);
      const int end = std::min(n, position + range + 1);  // exclusive
      ++points[start];
      --points[end];
    }

    int count = 0;
    int prefix = 0;
    for (int i = 0; i < n; ++i) {
      prefix += points[i];

      if (prefix >= requirement[i]) {
        ++count;
      }
    }
    return count;
  }
};
