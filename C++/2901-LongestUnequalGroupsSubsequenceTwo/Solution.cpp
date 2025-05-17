#include <algorithm>
#include <array>
#include <ranges>
#include <string>
#include <string_view>
#include <tuple>
#include <utility>
#include <vector>

class Solution {
 public:
  std::vector<std::string> getWordsInLongestSubsequence(
      std::vector<std::string>& words,
      std::vector<int>& groups) {
    // could just solve the problem without grouping by length....
    const int n = words.size();
    std::vector<int> dp(n, 1);
    std::vector<int> parent(n, -1);
    int bestLast = 0;

    auto valid = [&](int i, int j) {
      if (groups[i] == groups[j]) {
        return false;
      }

      std::string_view s = words[i];
      std::string_view t = words[j];
      if (s.size() != t.size()) {
        return false;
      }
      int diff = 0;
      for (auto [c1, c2] : std::ranges::views::zip(s, t)) {
        diff += c1 != c2;
      }
      return diff == 1;
    };

    for (int i = 1; i < n; ++i) {
      for (int j = 0; j < i; ++j) {
        if (valid(i, j) && dp[j] + 1 > dp[i]) {
          dp[i] = dp[j] + 1;
          parent[i] = j;
        }
      }

      if (dp[i] > dp[bestLast]) {
        bestLast = i;
      }
    }

    std::vector<std::string> result;
    for (int i = bestLast; i != -1; i = parent[i]) {
      result.emplace_back(std::move(words[i]));
    }
    std::reverse(result.begin(), result.end());
    return result;
  }

  std::vector<std::string> getWordsInLongestSubsequenceNaive(
      std::vector<std::string>& words,
      std::vector<int>& groups) {
    // The hamming distance between two strings of equal length is the number
    // of positions at which the corresponding characters are different.
    // Select the longest subequence of indices from [0..n-1] such that
    // - for adjacent indices in the subequence, groups[i-1] != groups[i].
    // - words[i-1] and words[i] are equal in length, and their hamming distance
    //   is 1.
    // 1 <= words[i].length <= 10
    // We can solve the sub-problem for each length, considering the second
    // requirement of equal lengths.
    // i.e., collect into array of vectors.
    const int n = words.size();
    std::array<std::vector<int>, 11> byLen{};
    for (int i = 0; i < n; ++i) {
      byLen[words[i].size()].push_back(i);
    }

    auto hamming = [](std::string_view s, std::string_view t) -> int {
      int diff = 0;
      for (auto [a, b] : std::ranges::views::zip(s, t)) {
        diff += a != b;
      }
      return diff;
    };

    auto lis = [&](std::vector<int>& indices)
        -> std::tuple<int, int, std::vector<int>> {
      // O(N^2) in terms of hamming distance.
      const int n = indices.size();
      int longest = 1;
      int start = 0;  // start backtracking

      // LIS ending at indices[i]
      std::vector<int> parent(n, -1);
      std::vector<int> dp(n, 1);
      for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
          int dist = hamming(words[indices[i]], words[indices[j]]);

          if (dist == 1 && groups[indices[i]] != groups[indices[j]]) {
            if (dp[j] + 1 > dp[i]) {
              dp[i] = dp[j] + 1;
              parent[i] = j;
            }
          }
        }

        if (dp[i] > longest) {
          longest = dp[i];
          start = i;
        }
      }

      // WARNING: the parent index here is not the global index. Must be
      // converted.
      return {longest, start, parent};
    };

    int longest = 0;
    int start = -1;
    int groupLen = -1;
    std::vector<int> parent;
    for (int len = 1; len <= 10; ++len) {
      if (byLen[len].empty()) {
        continue;
      }

      auto [l, st, par] = lis(byLen[len]);
      if (l > longest) {
        longest = l;
        start = st;
        groupLen = len;
        parent = std::move(par);
      }
    }

    // backtrack on parents
    std::vector<std::string> result;
    auto& indices = byLen[groupLen];
    for (int i = start; i != -1; i = parent[i]) {
      result.push_back(std::move(words[indices[i]]));
    }
    std::reverse(result.begin(), result.end());
    return result;
  }
};
