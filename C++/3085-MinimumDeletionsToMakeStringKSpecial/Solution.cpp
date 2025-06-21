#include <algorithm>
#include <array>
#include <cstdlib>
#include <limits>
#include <string_view>

class Solution {
 public:
  int minimumDeletions(std::string_view word, int k) {
    // We consider word to be k-special if |freq(word[i]) - freq(word[j])|<=k
    // for all indices i, j.
    // Return the minimum number of deletions to make word k special.
    // Count the min and max frequency, then delete the max-frequency one?
    // Ahhhh.
    // There is an edge case, where we can remove all occurences of
    // an element by deleting it until it becomes 0.
    // Zzz. We may need to delete from the maximum too, but evenly.
    std::array<int, 26> freq{};
    for (char c : word) {
      ++freq[c - 'a'];
    }

    int minDeletions = std::numeric_limits<int>::max();
    // fix each character as the minimum.
    for (int i = 0; i < 26; ++i) {
      if (freq[i] == 0) {
        continue;
      }

      int deletions = 0;
      for (int j = 0; j < 26; ++j) {
        if (freq[j] == 0 || i == j) {
          continue;
        }
        if (freq[j] < freq[i]) {
          // since we fix char i as the min, we obviously need to delete j if
          // freq[j] < freq[i].
          deletions += freq[j];
        } else {
          deletions += std::max((freq[j] - freq[i]) - k, 0);
        }
      }
      minDeletions = std::min(minDeletions, deletions);
    }

    return minDeletions;
  }
};
