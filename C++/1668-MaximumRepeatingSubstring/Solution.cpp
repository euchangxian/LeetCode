#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <string_view>

class Solution {
 public:
  int maxRepeating(std::string_view sequence, std::string_view word) {
    // A word is k-repeating if word concatenated k times is a substring of
    // sequence, where k >= 0.
    // Return k.
    // Given constraints, brute force string comparison is sufficient.
    // i.e., iterate k * word.size() <= sequence.size().
    // Can we do better is probably KMP/Rolling Hashes.
    // Another optimization is to iterate over the starting indices of the
    // sequence, upon encountering a substring of k * word, extend and check
    // (k+1)*word. If failed, then skip the entire range.
    int n = word.size();
    int maxK = 0;
    for (int start = 0; start + n <= sequence.size(); ++start) {
      if (sequence.substr(start, n) == word) {
        int k = 1;
        int pos = start + n;

        while (pos + n <= sequence.size() && sequence.substr(pos, n) == word) {
          ++k;
          pos += n;
        }

        maxK = std::max(maxK, k);
      }
    }
    return maxK;
  }
};
