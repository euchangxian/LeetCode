#include <algorithm>
#include <array>
#include <string_view>
#include <vector>

class Solution {
 public:
  std::vector<int> partitionLabels(std::string_view s) {
    // determine for each character the first and last index it occurs.
    // Then we get a list of intervals.
    // Becomes Merge Intervals
    // Two Pass.
    std::array<int, 256> last;
    for (int i = 0; i < s.size(); ++i) {
      last[s[i]] = i;
    }

    std::vector<int> result;
    result.reserve(s.size());

    int start = 0;
    int furthestEnd = -1;
    for (int i = 0; i < s.size(); ++i) {
      furthestEnd = std::max(furthestEnd, last[s[i]]);

      if (furthestEnd <= i) {
        result.push_back(i - start + 1);
        start = i + 1;
      }
    }
    return result;
  }
};
