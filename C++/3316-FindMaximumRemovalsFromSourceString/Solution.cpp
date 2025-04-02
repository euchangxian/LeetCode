#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <string_view>
#include <vector>

constexpr int MAX_N = 3 * 1e3;

class Solution {
 public:
  int maxRemovals(std::string_view source,
                  std::string_view pattern,
                  std::vector<int>& targetIndices) {
    // Naively, define isSubsequence(src, pattern) which takes O(n) time
    // Then, for each targetIndices, try removing it in a backtracking fashion.
    // Let n be the length of the source string, m be the size of the indices.
    // Then this will take O(2^m * n) time.
    // Can we do better?
    //
    // Determine the characters that would be removed by the targetIndices.
    // Something like two pointer? Initialize to the first and last indices.
    // If the character is not part of the pattern, then it can be removed
    // trivially. Move to the next index.
    // If part of the pattern, then advance the pattern index? I.e., maintain
    // 4 pointers, 2 for the source/targetIndices, 2 for the pattern.
    // E.g.,
    // source = "yeyeykyded"
    // iter 1:   ^   ^          match left, advance left ptrs.
    // iter 2:    ^  ^          no match right, Advance tRight. removals = 1
    //
    // pattern = "yeyyd"
    // iter 1:     ^ ^
    // targetIndices = [0, 2, 3, 4]
    //
    // oh... the issue is that we may wrongly remove characters that form the
    // subsequence outside of the two pointers.
    //
    // Let's go back to DP.
    // Given that the input is generated such that pattern initially appears as
    // as subsequence in source, we can reframe this problem slightly.
    //
    // Let dp[i] represent the maximum number of removals from s[:i].
    // Then we can memoize the two choices earlier.
    const int m = source.size();
    const int n = pattern.size();
    std::bitset<MAX_N + 1> remove{};
    for (int x : targetIndices) {
      remove[x] = 1;
    }

    // Refer to top-down approach
    std::array<int, MAX_N + 1> dp;
    std::fill(dp.begin(), dp.end(), INT_MIN);
    dp[n] = 0;

    for (int i = m - 1; i >= 0; --i) {
      for (int j = 0; j <= n; ++j) {
        dp[j] += remove[i];

        if (source[i] == pattern[j]) {
          dp[j] = std::max(dp[j], dp[j + 1]);
        }
      }
    }
    return dp[0];
  }

  int maxRemovalsMemo(std::string_view source,
                      std::string_view pattern,
                      std::vector<int>& targetIndices) {
    const int m = source.size();
    const int n = pattern.size();
    std::bitset<MAX_N + 1> remove{};
    for (int x : targetIndices) {
      remove[x] = 1;
    }

    // dp[i][j] represents the max removals from source[i:], while still
    // maintaining pattern[j:]
    std::vector<std::vector<int>> memo(m, std::vector<int>(n, -1));
    return dfs(source, pattern, remove, memo, 0, 0);
  }

 private:
  int dfs(std::string_view source,
          std::string_view pattern,
          std::bitset<MAX_N + 1>& remove,
          std::vector<std::vector<int>>& memo,
          int i,
          int j) {
    if (i >= source.size()) {
      if (j >= pattern.size()) {
        return 0;  // no more removals from source anyways.
      }

      // not possible to form a subsequence of pattern
      // Need to use a number other than -1 to denote this.
      // INT_MIN is used to simplify std::max.
      return INT_MIN;
    }

    // reached end of pattern. All susbequent targetIndices can be removed.
    if (j >= pattern.size()) {
      return remove[i] + dfs(source, pattern, remove, memo, i + 1, j);
    }

    int& ans = memo[i][j];
    if (ans != -1) {
      return memo[i][j];
    }

    // dont match current pattern.
    ans = remove[i] + dfs(source, pattern, remove, memo, i + 1, j);

    // match current pattern, dont remove.
    if (source[i] == pattern[j]) {
      ans = std::max(ans, dfs(source, pattern, remove, memo, i + 1, j + 1));
    }
    return ans;
  }
};
