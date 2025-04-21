#include <algorithm>
#include <array>
#include <vector>

constexpr int MAX_M = 100 + 2;
constexpr int INF = 0x3F3F3F3F;
class Solution {
 public:
  int minCost(int n, std::vector<int>& cuts) {
    cuts.push_back(0), cuts.push_back(n);
    std::sort(cuts.begin(), cuts.end());
    const int m = cuts.size();

    // std::vector<std::vector<int>> dp(m, std::vector<int>(m, INF));
    std::array<std::array<int, MAX_M>, MAX_M> dp;
    std::memset(dp.data(), INF, sizeof(dp));
    for (int i = 0; i < m - 1; ++i) {
      dp[i][i + 1] = 0;  // no internal cuts
    }

    for (int i = m - 1; i >= 0; --i) {
      for (int j = i + 1; j < m; ++j) {
        for (int k = i + 1; k < j; ++k) {
          dp[i][j] =
              std::min(dp[i][j], dp[i][k] + dp[k][j] + (cuts[j] - cuts[i]));
        }
      }
    }
    return dp[0][m - 1];
  }

  int minCostMemo(int n, std::vector<int>& cuts) {
    // Given stick labelled from 0 to n. (NOT n-1)
    // and cuts[i] which denotes the position a cut should be applied.
    // The cost of a cut is the length of the stick to be cut.
    // Reorder the cuts to obtain the minimum cost.
    // memo[i][j] which represents the minimum cost of cutting [i..j]?
    // Then, the transitions would involve (memo[i][k] + memo[k][j] + (j-i))
    // for all possible cuts[x] = k
    // Ah... N <= 1e6.
    // Memoization based on N will MLE.

    // Sentinel values, so that we can represent the start and end of the stick
    // using cuts[0], cuts[m].
    // NOTE: by doing so, we sort of change the representation of this cuts
    // array to something similar to points on the stick.
    // Where for each (i, j), find k > i, k < j such that we split (i, k) and
    // (k, j)
    cuts.push_back(0), cuts.push_back(n);
    std::sort(cuts.begin(), cuts.end());

    const int m = cuts.size();
    std::vector<std::vector<int>> memo(m, std::vector<int>(m, -1));
    return dfs(cuts, memo, 0, m - 1);
  }

 private:
  int dfs(std::vector<int>& points,
          std::vector<std::vector<int>>& memo,
          int i,
          int j) {
    if (j - i < 2) {
      return 0;  // Only two points, no way to cut in between
    }

    int& ans = memo[i][j];
    if (ans != -1) {
      return ans;
    }

    ans = INF;
    for (int k = i + 1; k < j; ++k) {
      ans = std::min(ans, dfs(points, memo, i, k) + dfs(points, memo, k, j) +
                              (points[j] - points[i]));
    }

    return ans;
  }
};
