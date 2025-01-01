#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <string_view>

class Solution {
 public:
  int maxScore(std::string_view s) {
    // seems related to prefix/suffix
    // Iterate over all possible points to split. Can first count the number of
    // '0's/'1's, and then maintain a running count.
    // Each '1' we see decreases the maxScore by 1, (must handle non-empty
    // splits)
    // Then, each '0' we see increases the score by 1.
    int score = std::ranges::count(s, '1');

    // not initialized to score, since that would mean the left substring is
    // empty.
    int max = 0;

    // NOTE the minus 1, since we won't want to consider the case where the
    // right substring is empty.
    for (int i = 0; i < s.size() - 1; ++i) {
      if (s[i] == '1') {
        --score;
      } else {
        ++score;
      }

      max = std::max(max, score);
    }

    return max;
  }
};
