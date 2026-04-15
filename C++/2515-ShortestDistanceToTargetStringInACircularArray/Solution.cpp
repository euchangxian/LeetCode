#include <string>
#include <string_view>
#include <vector>

class Solution {
 public:
  int closestTarget(std::vector<std::string>& words,
                    std::string_view target,
                    int startIndex) {
    // Circular string array words, target string.
    // Return the shortest distance needed to reach target, from startIndex,
    // or -1.
    //
    // Cannot just find the first-match.
    // Must traverse both directions.
    const auto n = static_cast<int>(words.size());
    for (int i = 0; i < n; ++i) {
      auto right = (startIndex + i) % n;
      auto left = (startIndex - i + n) % n;

      if (words[right] == target || words[left] == target) {
        return i;
      }
    }

    return -1;
  }
};
