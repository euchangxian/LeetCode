#include <algorithm>
#include <string>
#include <vector>

class Solution {
 public:
  int maxScoreWords(std::vector<std::string>& words,
                    std::vector<char>& letters,
                    std::vector<int>& score) {
    // pre-compute scores and character count
    std::vector<int> wordScore = std::vector<int>(words.size(), 0);
    for (int i = 0; i < words.size(); ++i) {
      for (char c : words[i]) {
        wordScore[i] += score[c - 'a'];
      }
    }
    std::vector<int> count = std::vector<int>(26, 0);
    for (char c : letters) {
      ++count[c - 'a'];
    }
    return knapsack(words, wordScore, count, 0);
  }

 private:
  int knapsack(const std::vector<std::string>& words,
               const std::vector<int>& scores,
               std::vector<int>& count,
               int idx) {
    if (idx >= words.size()) {
      return 0;
    }
    int skip = knapsack(words, scores, count, idx + 1);

    int pickScore = scores[idx];

    // update count
    for (char c : words[idx]) {
      --count[c - 'a'];
      if (count[c - 'a'] < 0) {
        pickScore = 0;  // cannot take.
      }
    }
    pickScore += knapsack(words, scores, count, idx + 1);
    // backtrack count
    for (char c : words[idx]) {
      ++count[c - 'a'];
    }
    return std::max(skip, pickScore);
  };
};
