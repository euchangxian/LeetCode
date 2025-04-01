#include <algorithm>
#include <array>
#include <vector>

constexpr int MAX_N = 1e5;
constexpr int MAX_BRAINPOWER = 1e5;
class Solution {
 public:
  long long mostPoints(std::vector<std::vector<int>>& questions) {
    // questions[i] = [points, brainpower]
    // Answer questions in order, two choices:
    // - skip.
    // - answer. Gain points, the next brainpower questions cannot be answered.
    // Maximum points you can gain.
    // Feels like Buy and Sell stock with cooldown or something.
    // Feels like iterate in reverse.
    // dp[i] = max{
    //   dp[i+1],       // skip current.
    //   p + dp[i+b+1] // maximum points from when the next qn can be answered
    // }
    //
    // Naively, pick a question, skip the subsequent brainpower questions,
    // or       skip this question.
    // Then, the maximum points gained can be modelled with:
    // dfs(idx) {
    //   return max(
    //     dfs(idx+1),
    //     p + dfs(idx + b + 1)
    //   )
    // }
    const int n = questions.size();

    // add sentinel values to simplify bounds check.
    std::array<long long, MAX_N + MAX_BRAINPOWER + 1> dp{};
    for (int i = n - 1; i >= 0; --i) {
      int p = questions[i][0], b = questions[i][1];
      dp[i] = std::max(dp[i + 1], p + dp[i + b + 1]);
    }
    return dp[0];
  }

  long long mostPointsMemo(std::vector<std::vector<int>>& questions) {
    // questions[i] = [points, brainpower]
    // Answer questions in order, two choices:
    // - skip.
    // - answer. Gain points, the next brainpower questions cannot be answered.
    // Maximum points you can gain.
    // Feels like Buy and Sell stock with cooldown or something.
    // Feels like iterate in reverse.
    // dp[i] = max{
    //   dp[i+1],       // skip current.
    //   p + dp[i+b+1] // maximum points from when the next qn can be answered
    // }
    //
    // Naively, pick a question, skip the subsequent brainpower questions,
    // or       skip this question.
    // Then, the maximum points gained can be modelled with:
    // dfs(idx) {
    //   return max(
    //     dfs(idx+1),
    //     p + dfs(idx + b + 1)
    //   )
    // }
    const int n = questions.size();

    std::vector<long long> memo(n + 1, -1);
    return dfs(questions, memo, 0);
  }

 private:
  long long dfs(const std::vector<std::vector<int>>& questions,
                std::vector<long long>& memo,
                int idx) {
    if (idx >= questions.size()) {
      return 0;
    }

    long long& ans = memo[idx];
    if (ans != -1) {
      return ans;
    }

    int points = questions[idx][0], brainpower = questions[idx][1];
    ans = std::max(dfs(questions, memo, idx + 1),
                   points + dfs(questions, memo, idx + 1 + brainpower));
    return ans;
  }
};
