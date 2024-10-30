#include <climits>
#include <cstddef>
#include <utility>
#include <vector>

using namespace std;
class Solution {
 public:
  int minCostII(vector<vector<int>>& costs) {
    // Row of n houses, each house can be painted with one of k colors.
    // Cost of painting each house with a certain color is different.
    //
    // Paint all the houses such that no two adjacent houses have the same
    // color.
    //
    // Given n * k matrix costs, where cost[0][0] indicate the cost of
    // painting house 0 with color 0 is cost[0][0].
    //
    // Return minimum cost to paint all houses with the above condition.
    //
    // First glance looks like House Robber...
    //
    // At each house (except the first), there are (k-1) possible decisions,
    // as long as it does not have the same colour as the previous house.
    //
    // Hm. Therefore we can have dp[i][j], where dp[i][j] represent the cost of
    // coloring the first i houses, and the last house is painted with the jth
    // colour?
    // Whatever. Lets try going top-down/naive first...
    //
    // minCost := 0
    // def dfs(costs, minCost, currCost, idx, prevColor):
    //   if idx >= n then minCost = min(minCost, currCost)
    //
    //   for j in [0..k]:
    //     if j == prevColor then continue
    //     dfs(costs, minCost, currCost + costs[idx][j], idx + 1, j)
    //
    // dfs(costs, minCosts, 0, 0, -1)
    // return minCost
    //
    // Time complexity: O(k^n), k decisions, n depth.
    //
    // Hm. How can we memoize and avoid recomputing repeated work?
    // State is definitely the idx. What about color? Do we use dp[i][j] to
    // represent the current ith house with the color j, or the previous (i-1)th
    // house with color j?
    //
    // Seems like it should be color the ith house with color j.
    //
    // What about the subproblems? Seems like it takes O(k) time for each i, j
    // to walk through the colors and update.
    // In a sense, I believe this is repeated work... Can we maintain the
    // minimum of the current dp[i][j], then use it in the next iteration?
    // Hm. Minimum and 2nd Minimum, accounting for the case where the
    // color cannot be reused.

    // Then a final traversal through dp[n-1] to figure out the minimum.
    // O(nk^2)?
    //
    // Follow Up: solve in O(nk) runtime... Precomputation?
    //
    // See LeetCode for the 3 different variants:
    // 1. O(nk^2) => for each (i, j), find the min of dp[i-1] in O(k) time
    // 2. O(nk) => maintain the firstMin/secondMin of dp[i-1].
    // 3. O(1) space => Update the costs in-place.

    const size_t n = costs.size();
    const size_t k = costs[0].size();

    // {color, cost}
    std::pair<size_t, int> firstMin = {-1, INT_MAX};
    std::pair<size_t, int> secondMin = {-1, INT_MAX};
    for (size_t j = 0; j < k; ++j) {
      if (costs[0][j] < firstMin.second) {
        secondMin = firstMin;
        firstMin = {j, costs[0][j]};
      } else if (costs[0][j] < secondMin.second) {
        secondMin = {j, costs[0][j]};
      }
    }

    for (size_t i = 1; i < n; ++i) {
      std::pair<size_t, int> currFirstMin = {-1, INT_MAX};
      std::pair<size_t, int> currSecondMin = {-1, INT_MAX};
      for (size_t j = 0; j < k; ++j) {
        // Choose either the first/second min of the previous (i-1)th houses.
        if (j != firstMin.first) {
          costs[i][j] += firstMin.second;
        } else {
          costs[i][j] += secondMin.second;
        }

        // Update the min of the current iteration
        if (costs[i][j] < currFirstMin.second) {
          currSecondMin = currFirstMin;
          currFirstMin = {j, costs[i][j]};
        } else if (costs[i][j] < currSecondMin.second) {
          currSecondMin = {j, costs[i][j]};
        }
      }

      firstMin = currFirstMin;
      secondMin = currSecondMin;
    }

    return firstMin.second;
  }
};
