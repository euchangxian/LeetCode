#include <algorithm>
#include <climits>
#include <cstddef>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
/**
 * shortest distance between word1 and word2 in the array wordDict is defined
 * as the shortest difference between the indices of word1 and word2 in the
 * array.
 *
 * Each word can appear multiple times at different positions. How to
 * efficiently find the smallest distance?
 * Naively seems to be maintaining a map of strings to a vector of indices.
 * Then, find the smallest range that overlaps. Linear search exploiting the
 * sorted property of the indices.
 *
 * Similar to LeetCode 632.
 */
class WordDistance {
 private:
  unordered_map<string, vector<size_t>> indices;

 public:
  WordDistance(vector<string>& wordsDict) {
    for (size_t i = 0; i < wordsDict.size(); ++i) {
      indices[wordsDict[i]].push_back(i);
    }
  }

  int shortest(const string& word1, const string& word2) {
    vector<size_t> indices1 = indices[word1];
    vector<size_t> indices2 = indices[word2];

    size_t i = 0;
    size_t j = 0;

    int minRange = INT_MAX;
    // advance the lower-valued ptr.
    while (i < indices1.size() && j < indices2.size()) {
      const int idx1 = indices1[i];
      const int idx2 = indices2[j];

      minRange =
          min(minRange, abs(static_cast<int>(idx2) - static_cast<int>(idx1)));

      if (idx1 < idx2) {
        ++i;
      } else {
        ++j;
      }
    }
    return minRange;
  }
};

/**
 * Your WordDistance object will be instantiated and called as such:
 * WordDistance* obj = new WordDistance(wordsDict);
 * int param_1 = obj->shortest(word1,word2);
 */
