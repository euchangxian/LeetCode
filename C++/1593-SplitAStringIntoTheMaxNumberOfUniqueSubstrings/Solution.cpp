#include <algorithm>
#include <cstddef>
#include <string_view>
#include <unordered_set>

class Solution {
 public:
  int maxUniqueSplit(std::string_view s) {
    // Seems like greedy? Form substrings of length 1, then 2, ...
    // Given that 1 <= s.length <= 16, seems like a whole bunch of approaches
    // would be valid, including backtracking. Maintain a Set of substrings.
    // Contiguous though.
    // Greedy approach is not correct.
    // "w|ww|z|f|v|e|d|wf|vh|sww" => 10
    // "www|z|f|v|e|d|w|f|v|h|s|ww" => 11, where the least locally optimal
    // choice is taken in 'www'.
    // DP is not entirely correct too.
    std::unordered_set<std::string_view> seen;
    int maxSplits = 0;
    dfsPrune(s, seen, maxSplits, 0, 0);
    return maxSplits;
  }

 private:
  void dfsPrune(std::string_view s,
                std::unordered_set<std::string_view>& seen,
                int& maxSplits,
                std::size_t start,
                int currSplits) {
    if (currSplits + (s.length() - start + 1) < maxSplits) {
      // if even after splitting the remaining substring into individual words,
      // the currSplits will not exceed the maxSplits, then just return early
      // and prune the subtree.
      return;
    }

    if (start >= s.length()) {
      maxSplits = std::max(maxSplits, currSplits);
      return;
    }

    // For each position, try splitting
    for (std::size_t len = 1; len <= s.length() - start; ++len) {
      // DFS
      std::string_view substr = s.substr(start, len);
      if (!seen.count(substr)) {
        seen.emplace(substr);

        dfsPrune(s, seen, maxSplits, start + len, currSplits + 1);

        seen.erase(substr);  // backtrack.
      }
    }
  }

  int dfs(std::string_view s,
          std::unordered_set<std::string_view>& seen,
          std::size_t start) {
    if (start >= s.length()) {
      return 0;  // No more splits can be made.
    }

    int maxSplits = 0;
    // For each position, try splitting
    for (std::size_t len = 1; len <= s.length() - start; ++len) {
      // DFS
      std::string_view substr = s.substr(start, len);
      if (!seen.count(substr)) {
        seen.emplace(substr);

        int splits = 1 + dfs(s, seen, start + len);
        maxSplits = std::max(maxSplits, splits);

        seen.erase(substr);  // backtrack.
      }
    }
    return maxSplits;
  }
};
