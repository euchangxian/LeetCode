#include <vector>

class Solution {
 public:
  int numberOfAlternatingGroups(std::vector<int>& colors, int k) {
    // circle of tiles, color[i] == 0|1, indicating tile i color.
    //
    // An alternating group is a group of k tiles, where each tile has
    // alternating colors.
    // Sliding window of size k? Need to be able to determine when a pattern is
    // no longer valid though.
    const int n = colors.size();

    int result = 0;
    int alternating = 1;  // size of the valid window with alternating elements.
    int prev = colors[0];
    for (int i = 1; i < n + k - 1; ++i) {
      int idx = i % n;

      if (colors[idx] == prev) {
        alternating = 1;  // reset
      } else {
        ++alternating;
      }

      if (alternating >= k) {
        ++result;
      }
      prev = colors[idx];
    }
    return result;
  }
};
