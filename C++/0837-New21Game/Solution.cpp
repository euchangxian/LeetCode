#include <array>
#include <numeric>

constexpr int MAX_NK = 1E4;
constexpr int MAX_POINTS = 1E4;
class Solution {
 public:
  double new21Game(int n, int k, int maxPts) {
    // Alice starts with 0 points, draws number while she has less than k
    // points.
    // During each draw, gains an integer number from the range [1..maxPts].
    // Each draw is independent.
    // Stop drawing when k or more points.
    // Return the probability that Alice has n or fewer points.
    //
    // Or 1 - P(X>n)?
    // The overlapping subproblems are clear:
    // P(X=x) = P(X=x-1) + ... + P(X=x-maxPts)
    // Then, P(X<=n) = P(X=1) + ... + P(X=n)
    //
    // dp[k], where k is the sum of points in the ith-draw?
    // Minimally k draws - 1 point each. But k<=n and we are interested in <=n.

    std::array<double, MAX_NK + 1> dp{};
    dp[0] = 1.0;

    double psum = k > 0 ? 1.0 : 0.0;

    for (int i = 1; i <= n; ++i) {
      dp[i] = psum / maxPts;

      if (i < k) {
        psum += dp[i];
      }

      if (i - maxPts >= 0 && i - maxPts < k) {
        psum -= dp[i - maxPts];
      }
    }

    return std::accumulate(dp.begin() + k, dp.begin() + n + 1, 0.0);
  }
};
