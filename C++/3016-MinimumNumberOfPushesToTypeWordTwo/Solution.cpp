#include <algorithm>
#include <string>
#include <vector>

class Solution {
 public:
  int minimumPushes(std::string word) {
    std::vector<int> frequencies(26, 0);
    for (char c : word) {
      ++frequencies[c - 'a'];
    }

    // Sort in Descending order of frequencies.
    // There is no need to store the mapping of characters to frequencies.
    std::sort(frequencies.rbegin(), frequencies.rend());

    // Greedily assign the mapping.
    // The highest 8 (2 to 9 button) frequencies will be assigned to have 1
    // button push The next 8 will be assigned to require 2 button pushes and so
    // on.
    int minPushes = 0;
    for (int i = 0; i < 26; ++i) {
      if (!frequencies[i]) {
        break;
      }

      minPushes += ((i / 8) + 1) * frequencies[i];
    }

    return minPushes;
  }
};
