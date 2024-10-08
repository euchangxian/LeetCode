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

using ll = long long;
using namespace std;
class Solution {
 public:
  ll maxPoints(vector<vector<int>> const& points) {
    // Problem: Choose one point from each row to maximize total points,
    // subtracting abs(c1 - c2) for the distance between chosen points in
    // adjacent rows.

    // Optimal Substructure:
    // If (rx, cx) is picked, the max points from (r0, c0) to (rx, cx) is
    // max points from (r0, c0) to (rx-1, cx-1) + points at (rx, cx) - penalty.

    // Not Greedy: Consider the example:
    // 2 1 1 1 : Pick (0, 0): 2 points
    // 1 1 2 1 : Greedy would pick (1, 2): 2 + 2 - abs(2 - 0) = 2 points
    // Optimal is (0, 0) -> (1, 0): 2 + 1 = 3 points

    // Optimization Insight:
    // 1. The penalty for picking a previous cell is recomputed multiple times
    //    when iterating through the current row.
    // 2. We can use running maximum values (prefixMax and postfixMax) to avoid
    //    recomputing penalties.
    int m = points.size();
    int n = points[0].size();

    // prevRow[j] represents the max sum obtainable from picking the (i-1, j)-th
    // cell.
    vector<ll> prevRow(n);
    for (int j = 0; j < n; ++j) {
      prevRow[j] = points[0][j];
    }

    for (int i = 1; i < m; ++i) {
      // Pre-processing: Calculate prefixMax and postfixMax using prevRow
      // values.

      // prefixMax[j] is the max value considering cells to the left (k <= j)
      vector<ll> prefixMax(n);
      prefixMax[0] = prevRow[0];
      for (int j = 1; j < n; ++j) {
        // Max of cell directly above and prefixMax of left cells minus distance
        // penalty
        prefixMax[j] = max(prevRow[j], prefixMax[j - 1] - 1);
      }

      // postfixMax[j] is the max value considering cells to the right (k >= j)
      vector<ll> postfixMax(n);
      postfixMax[n - 1] = prevRow[n - 1];
      for (int j = n - 2; j >= 0; --j) {
        postfixMax[j] = max(prevRow[j], postfixMax[j + 1] - 1);
      }

      // Update prevRow using pre-computed maximum sums including penalties
      for (int j = 0; j < n; ++j) {
        prevRow[j] = max(prefixMax[j], postfixMax[j]) + points[i][j];
      }
    }

    return *max_element(prevRow.begin(), prevRow.end());
  }

  ll maxPointsNaive(vector<vector<int>> const& points) {
    int m = points.size();
    int n = points[0].size();

    vector<vector<ll>> dp(m, vector<ll>(n));

    // base case, first row does not have penalty
    for (int j = 0; j < n; ++j) {
      dp[0][j] = points[0][j];
    }

    for (int i = 1; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        // Another loop to check the maximum sum given the penalty
        // for each cell
        for (int k = 0; k < n; ++k) {
          dp[i][j] = max(dp[i][j], points[i][j] + dp[i - 1][k] - abs(j - k));
        }
      }
    }

    return *max_element(dp[m - 1].begin(), dp[m - 1].end());
  }
};
