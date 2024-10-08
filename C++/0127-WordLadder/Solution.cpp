#include <algorithm>
#include <climits>
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
  int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    unordered_set<string> words(wordList.begin(), wordList.end());
    if (!words.count(endWord)) {
      return 0;
    }

    queue<vector<string>> frontiers;
    frontiers.push({beginWord});

    int result = 0;
    while (!frontiers.empty()) {
      vector<string> frontier = frontiers.front();
      frontiers.pop();
      ++result;

      vector<string> nextFrontier;
      for (string curr : frontier) {
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
