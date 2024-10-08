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
  vector<int> findSubstring(string s, vector<string>& words) {
    // All string of words are same length
    // A concatenated string is a string the exactly contains all the strings
    // of any permutation of words combined.
    // To find starting indices of all concatenated substrings
    //
    // Since the substring must contain all characters in words, we can use
    // a fixed-size sliding window.

    int wordCount = words.size();
    int wordLength = words[0].size();
    if (s.length() < words.size() * wordLength) {
      return {};
    }

    unordered_map<string, int> expectedFreq;
    for (auto const& word : words) {
      ++expectedFreq[word];
    }

    vector<int> result;
    result.reserve(s.length());

    // E.g. if wordLength = 3, s = "abcdefghi",
    // offset = 0 => "abc", "cde", "fgh"
    // offset = 1 => "bcd", "efg"
    // offset = 2 => "cde", "fgh"
    for (int offset = 0; offset < wordLength; ++offset) {
      unordered_map<string, int> windowFreq;

      // Counts the number of words in the window that fulfil expectedFreq
      int validWords = 0;
      int left = offset;
      for (int right = offset; right + wordLength - 1 < s.length();
           right += wordLength) {
        string currentWord = s.substr(right, wordLength);

        if (!expectedFreq.count(currentWord)) {
          windowFreq.clear();
          validWords = 0;
          left = right + wordLength;  // Move left bound
          continue;
        }

        ++windowFreq[currentWord];

        if (windowFreq[currentWord] <= expectedFreq[currentWord]) {
          ++validWords;
        } else {
          // Adjust window left
          while (windowFreq[currentWord] > expectedFreq[currentWord]) {
            string leftWord = s.substr(left, wordLength);
            --windowFreq[leftWord];

            if (windowFreq[leftWord] < expectedFreq[leftWord]) {
              // Condition is no longer met
              --validWords;
            }
            left += wordLength;
          }
        }

        if (validWords == wordCount) {
          result.push_back(left);
        }
      }
    }

    return result;
  }
};
