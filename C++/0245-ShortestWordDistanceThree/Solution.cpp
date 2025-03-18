#include <algorithm>
#include <climits>
#include <cstddef>
#include <string>
#include <vector>

class Solution {
 public:
  int shortestWordDistance(std::vector<std::string>& wordsDict,
                           const std::string& word1,
                           const std::string& word2) {
    // Same similar as shortestWordDistanceTwo.
    // Collect all indices of word1 and word2. Then linear search.
    // word1 may be equal to word2. But it is guaranteed that they are at least
    // two distinct words.
    std::vector<int> indices1;
    std::vector<int> indices2;
    for (size_t i = 0; i < wordsDict.size(); ++i) {
      if (wordsDict[i] == word1) {
        indices1.push_back(i);
      } else if (wordsDict[i] == word2) {
        // Else is important to ensure that if word1 and word2 are the same,
        // then only indices1 will be populated, allowing cleaner handling of
        // this edge case.
        indices2.push_back(i);
      }
    }

    // find smallest adjacent distance
    int range = INT_MAX;
    if (word1 == word2) {
      for (size_t i = 1; i < indices1.size(); ++i) {
        range = std::min(range, indices1[i] - indices1[i - 1]);
      }
      return range;
    }

    // otherwise find smallest overlapping range.
    int i = 0;
    int j = 0;
    while (i < indices1.size() && j < indices2.size()) {
      const int idx1 = indices1[i];
      const int idx2 = indices2[j];

      range = std::min(range, std::abs(idx2 - idx1));
      if (idx1 < idx2) {
        ++i;
      } else {
        ++j;
      }
    }
    return range;
  }
};
