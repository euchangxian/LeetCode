#include <algorithm>
#include <cstddef>
#include <string_view>
#include <unordered_set>

using namespace std;
class Solution {
 private:
  void dfsPrune(string_view s,
                unordered_set<string_view>& seen,
                int& maxSplits,
                size_t start,
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
    for (size_t len = 1; len <= s.length() - start; ++len) {
      // DFS
      string_view substr = s.substr(start, len);
      if (!seen.count(substr)) {
        seen.emplace(substr);

        dfsPrune(s, seen, maxSplits, start + len, currSplits + 1);

        seen.erase(substr);  // backtrack.
      }
    }
  }
  int dfs(string_view s, unordered_set<string_view>& seen, size_t start) {
    if (start >= s.length()) {
      return 0;  // No more splits can be made.
    }

    int maxSplits = 0;
    // For each position, try splitting
    for (size_t len = 1; len <= s.length() - start; ++len) {
      // DFS
      string_view substr = s.substr(start, len);
      if (!seen.count(substr)) {
        seen.emplace(substr);

        int splits = 1 + dfs(s, seen, start + len);
        maxSplits = std::max(maxSplits, splits);

        seen.erase(substr);  // backtrack.
      }
    }
    return maxSplits;
  }

 public:
  int maxUniqueSplit(string_view s) {
    // Seems like greedy? Form substrings of length 1, then 2, ...
    // Given that 1 <= s.length <= 16, seems like a whole bunch of approaches
    // would be valid, including backtracking. Maintain a Set of substrings.
    // Contiguous though.
    // Greedy approach is not correct.
    // "w|ww|z|f|v|e|d|wf|vh|sww" => 10
    // "www|z|f|v|e|d|w|f|v|h|s|ww" => 11, where the least locally optimal
    // choice is taken in 'www'.
    // DP is not entirely correct too.
    unordered_set<string_view> seen;
    int maxSplits = 0;
    dfsPrune(s, seen, maxSplits, 0, 0);
    return maxSplits;
  }
};
