#include <algorithm>
#include <string>
#include <vector>

class Solution {
 public:
  int shortestDistance(std::vector<std::string>& wordsDict,
                       std::string word1,
                       std::string word2) {
    // word1 and word2 are not guaranteed to be unique in wordsDict
    int idx1 = -1;
    int idx2 = -1;
    int minDist = wordsDict.size();

    for (std::size_t i = 0; i < wordsDict.size(); ++i) {
      if (wordsDict[i] == word1) {
        idx1 = i;
      } else if (wordsDict[i] == word2) {
        idx2 = i;
      }

      if (idx1 != -1 && idx2 != -1) {
        minDist = std::min(minDist, abs(idx1 - idx2));
      }
    }

    return minDist;
  }
};
