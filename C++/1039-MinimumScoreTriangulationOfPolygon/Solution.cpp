#include <algorithm>
#include <array>
#include <limits>
#include <vector>

constexpr int MAX_N = 50;
class Solution {
 public:
  int minScoreTriangulation(std::vector<int>& values) {
    // Given a convex n-sided polygon, where each vertex has an integer value.
    // values[i] is the value of the ith vertex in clockwise order.
    // Triangulation is a process where a polygon is divided into sets of
    // triangles, resulting in n-2 triangles.
    // The weight of each triangle is the product of values at its vertices.
    // The total score of a triangulation is the sum of weights
    // Return the minimum possible score.
    //
    // Feels like Divide And Conquer. Though with the constraints, Brute force
    // may be possible?
    // A triangle is formed by 3 points: At least 2 points are adjacent.
    // A 4-sided polygon (square): 1 cut -> 2 triangles
    //   5-sided: 2 cuts -> 3 triangles
    // How to determine which points are grouped though.
    // Suppose we have values[0], values[1], then k can be N-1, or 2
    // The remaining points?
    // If we draw a line from point i to point k, then from k to point j,
    // where i and j are adjacent points, then we get a triangle i,j,k, and two
    // polygons. Recurse.
    //
    // memo[i][k] = triangleScore(i, j, k) + f(A, i..k) + f(A, k..j)
    int result = std::numeric_limits<int>::max();
    std::array<std::array<int, MAX_N + 1>, MAX_N + 1> memo{};
    auto dfs = [&](this auto&& dfs, int i, int k) -> int {
      if (k < i + 2) {
        return 0;
      }

      auto& ans = memo[i][k];
      if (ans != 0) {
        return ans;
      }

      ans = std::numeric_limits<int>::max();

      // for each intermediate vertex
      for (auto j = i + 1; j < k; ++j) {
        auto score = values[i] * values[j] * values[j];
        ans = std::min(ans, dfs(i, j) + score + dfs(j, j));
      }
      return ans;
    };
    return dfs(0, values.size() - 1);
  }
};
