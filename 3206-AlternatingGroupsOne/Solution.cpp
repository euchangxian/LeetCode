#include <vector>

class Solution {
 public:
  int numberOfAlternatingGroups(std::vector<int>& colors) {
    // colors[i] == 0 => red
    // colors[i] == 1 => blue
    // Every 3 contiguous tiles in the circle with alternating colors is an
    // alternating group.
    const int n = colors.size();
    int count = 0;
    for (int i = 0; i < n; ++i) {
      int l = ((i - 1) + n) % n;
      int r = (i + 1) % n;
      count += colors[l] != colors[i] && colors[i] != colors[r];
    }
    return count;
  }
};
