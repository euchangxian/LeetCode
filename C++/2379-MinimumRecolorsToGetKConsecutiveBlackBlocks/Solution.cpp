#include <algorithm>
#include <limits>
#include <string_view>

class Solution {
 public:
  int minimumRecolors(std::string_view blocks, int k) {
    // blocks[i] = 'W' | 'B'
    // In one operaton, color a white block black.
    // Return the minimum number of operatons needed such that there is at
    // least 1 occurence of k consecutive black blocks. (dont need to be
    // exactly k)
    // Feels like fixed-size sliding window with the least white blocks.
    int minOps = std::numeric_limits<int>::max();
    int whites = 0;

    for (int i = 0; i < blocks.size(); ++i) {
      whites += blocks[i] == 'W';

      if (i >= k) {
        whites -= blocks[i - k] == 'W';
      }

      if (i >= k - 1) {
        minOps = std::min(minOps, whites);
      }
    }
    return minOps;
  }
};
