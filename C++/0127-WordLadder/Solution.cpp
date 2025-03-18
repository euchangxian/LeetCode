#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

class Solution {
 public:
  int ladderLength(std::string beginWord,
                   std::string endWord,
                   std::vector<std::string>& wordList) {
    std::unordered_set<std::string> words(wordList.begin(), wordList.end());
    if (!words.count(endWord)) {
      return 0;
    }

    std::queue<std::vector<std::string>> frontiers;
    frontiers.push({beginWord});

    int result = 0;
    while (!frontiers.empty()) {
      std::vector<std::string> frontier = frontiers.front();
      frontiers.pop();
      ++result;

      std::vector<std::string> nextFrontier;
      for (std::string curr : frontier) {
        if (curr == endWord) {
          return result;
        }

        // Find neighbours by swapping each character of the current word
        for (int i = 0; i < curr.length(); ++i) {
          char original = curr[i];
          for (char c = 'a'; c <= 'z'; ++c) {
            curr[i] = c;
            if (words.count(curr)) {
              nextFrontier.push_back(curr);
              words.erase(curr);  // mark as visited.
            }
          }
          curr[i] = original;  // Swap back
        }
      }

      // std::move avoids copy
      if (!nextFrontier.empty()) {
        frontiers.push(std::move(nextFrontier));
      }
    }

    // If there is no path
    return 0;
  }
};
