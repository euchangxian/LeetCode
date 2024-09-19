#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <cstddef>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class Solution {
public:
  int shortestDistance(vector<string> &wordsDict, string word1, string word2) {
    // word1 and word2 are not guaranteed to be unique in wordsDict
    int idx1 = -1;
    int idx2 = -1;
    int minDist = wordsDict.size();

    for (size_t i = 0; i < wordsDict.size(); ++i) {
      if (wordsDict[i] == word1) {
        idx1 = i;
      } else if (wordsDict[i] == word2) {
        idx2 = i;
      }

      if (idx1 != -1 && idx2 != -1) {
        minDist = min(minDist, abs(idx1 - idx2));
      }
    }

    return minDist;
  }
};
