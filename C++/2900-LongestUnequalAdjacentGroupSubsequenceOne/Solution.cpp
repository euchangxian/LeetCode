#include <cstddef>
#include <cstdlib>
#include <string>
#include <utility>
#include <vector>

class Solution {
 public:
  std::vector<std::string> getLongestSubsequence(
      std::vector<std::string>& words,
      std::vector<int>& groups) {
    // string array words, binary array groups of length n.
    // words[i] associated with groups[i]
    // Select Longest Alternating Subsequence from words.
    // A subsequence is alternating if for any two consecutive words in the
    // sequence, their corresponding elements in groups differ.
    // i.e., find longest groups[i] != groups[i+1] != groups[i+2] ...
    //
    // Similar to finding ZigZag subsequence.
    const int n = words.size();

    std::vector<std::string> result;
    result.reserve(n);
    result.push_back(std::move(words[0]));

    int prev = groups[0];
    for (int i = 1; i < n; ++i) {
      if (groups[i] != prev) {
        result.push_back(std::move(words[i]));
        prev = groups[i];
      }
    }
    return result;
  }
};
