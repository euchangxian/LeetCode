#include <algorithm>
#include <climits>
#include <cstddef>
#include <string>
#include <unordered_map>
#include <vector>

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
  std::unordered_map<std::string, std::vector<std::size_t>> indices;

 public:
  WordDistance(std::vector<std::string>& wordsDict) {
    for (std::size_t i = 0; i < wordsDict.size(); ++i) {
      indices[wordsDict[i]].push_back(i);
    }
  }

  int shortest(const std::string& word1, const std::string& word2) {
    std::vector<std::size_t> indices1 = indices[word1];
    std::vector<std::size_t> indices2 = indices[word2];

    std::size_t i = 0;
    std::size_t j = 0;

    int minRange = INT_MAX;
    // advance the lower-valued ptr.
    while (i < indices1.size() && j < indices2.size()) {
      const int idx1 = indices1[i];
      const int idx2 = indices2[j];

      minRange = std::min(
          minRange, std::abs(static_cast<int>(idx2) - static_cast<int>(idx1)));

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
