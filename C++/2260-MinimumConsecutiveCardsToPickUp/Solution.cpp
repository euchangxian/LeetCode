#include <algorithm>
#include <array>
#include <limits>
#include <vector>

constexpr int MAX_VAL = 1e6;

class Solution {
 public:
  int minimumCardPickup(std::vector<int>& cards) {
    std::array<int, MAX_VAL + 1> seen;
    std::memset(seen.data(), -1, sizeof(seen));

    int minConsecutive = std::numeric_limits<int>::max();
    for (int i = 0; i < cards.size(); ++i) {
      if (seen[cards[i]] != -1) {
        minConsecutive = std::min(minConsecutive, i - seen[cards[i]] + 1);
      }
      seen[cards[i]] = i;
    }

    return minConsecutive == std::numeric_limits<int>::max() ? -1
                                                             : minConsecutive;
  }
};
