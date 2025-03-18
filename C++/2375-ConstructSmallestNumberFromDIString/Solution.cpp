#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <string>
#include <string_view>

class Solution {
 public:
  std::string smallestNumber(std::string_view pattern) {
    // Starting with an increasing sequence,
    // we can reverse contiguous substrings corresponding to sequences of Ds
    const int n = pattern.size();
    std::string result;
    result.reserve(n + 1);
    auto begin = result.begin();
    for (int i = 0; i <= n; ++i) {
      result.push_back(i + '1');

      if (i >= n || pattern[i] == 'I') {
        std::reverse(begin, result.end());
        begin = result.begin() + i + 1;
      }
    }
    return result;
  }

  std::string smallestNumberDFS(std::string_view pattern) {
    // pattern[i] = I | D, increasing | decreasing.
    // Create a string num of length n+1, where
    // - num consists of the digits '1' to '9' only, each used at most once.
    // - if pattern[i] == I, then num[i] < num[i+1]
    // - if pattern[i] == D, then num[i] > num[i+1]
    // Return Lexicographically smallest.
    // Backtrack, starting from '1'. Try each pattern, backtrack if not
    // possible.
    // Checking the next index is a little weird. Do we check the previous
    // number?
    // Do we decide if the current digit is feasible by checking the next
    // possible digits?
    // Or do we try all 9 starting digits, then check the previous digits.
    const int n = pattern.size();
    std::string result(n + 1, ' ');
    int used = 0;
    dfs(n, pattern, used, result, 0);
    return result;
  }

 private:
  bool dfs(const int n,
           std::string_view pattern,
           int used,
           std::string& result,
           int idx) {
    if (idx >= n + 1) {
      return true;
    }

    int prev = idx > 0 ? result[idx - 1] - '0' : 0;
    for (int i = 1; i <= 9; ++i) {
      if (used & (1 << i)) {
        continue;
      }

      if (idx > 0) {
        if (pattern[idx - 1] == 'I' && i <= prev) {
          continue;
        }
        if (pattern[idx - 1] == 'D' && i >= prev) {
          continue;
        }
      }

      used |= (1 << i);
      result[idx] = i + '0';
      if (dfs(n, pattern, used, result, idx + 1)) {
        return true;
      }

      // backtrack
      used ^= (1 << i);
    }

    return false;
  }
};
