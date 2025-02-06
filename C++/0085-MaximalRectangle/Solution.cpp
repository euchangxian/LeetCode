#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <stack>
#include <vector>

class Solution {
 public:
  int maximalRectangle(std::vector<std::vector<char>>& matrix) {
    // binary matrix size rows x cols.
    // Find largest rectangle containing only '1's.
    // 1 <= row, cols <= 200
    // => r * c <= 4 * 10^4
    // Therefore, an O((r*c)^2) solution is AC.
    //
    // Very similar problem statement to Maximum Square.
    // But a Rectangle has less constraints.
    // dp[i][j] = min{
    //   dp[i-1][j],    // up
    //   dp[i][j-1],    // left
    //   dp[i-1][j-1]   // diagonal
    // }
    // will not work like for maximal square.
    //
    // Though, what if we were to track the maximum length/width possible at
    // each (r, c)?
    // i.e., longest vertical/horizontal chain of '1's ending at (r, c)
    // Nope, may come from different rectangles, causing over-estimation.
    //
    // What does a naive solution even look like?
    // For each '1' as a possible top-left corner of a rectangle, determine
    // the maximum vertical and horizontal?
    // Would require backtracking at each horiziontal to determine the maximum
    // vertical too (e.g., raindrop pattern)? Less naive?
    // For each '1' cell as the leftmost, find the longest '1' sequence starting
    // at (r, c).
    // Then, find the longest '1' sequence starting at each (r, c), column-wise?
    // Would then require a DFS on each cell (left-to-right) and (top-to-down)
    // to determine the minimum longest sequence vertically and horizontally
    // respectively. Seems like a pain to implement too.
    //
    // Adjusting abit, fixing one dimension of our rectangle, in this case,
    // height, first.
    // for each row i in [1..R]:
    //   for each row j in [i+1..R]:
    //     check if grid[k][c] == 1 for k in [i..j], like a line sweep.
    // allowing us to determine the maximum area. O(r^3 * c), since O(r^2) for
    // all pairs of rows, then O(rc) to scan cells.
    //
    // More feasible, and simpler to implement. Can we improve on this?
    // What is the repeated work?
    // Each cell in every column is repeatedly checked if they are '1',
    // particularly when incrementing row j.
    //
    // NOTE: Tapped out. I HATE DP
    // Viewing this in terms of rows, we get histograms of differing heights.
    // Therefore, for each row, maintain the current height of '1's, allowing
    // us to reduce it to LeetCode 84. Largest Rectangle in Histogram.
    const int rows = matrix.size();
    const int cols = matrix[0].size();

    std::vector<int> heights(cols);
    for (int c = 0; c < cols; ++c) {
      heights[c] = matrix[0][c] == '1';
    }

    int largestArea = largestRectangleArea(heights);
    for (int r = 1; r < rows; ++r) {
      for (int c = 0; c < cols; ++c) {
        heights[c] = matrix[r][c] == '1' ? heights[c] + 1 : 0;
      }
      largestArea = std::max(largestArea, largestRectangleArea(heights));
    }

    return largestArea;
  }

 private:
  // See LeetCode 84. Largest Rectangle in Histogram.
  // Essentially, a rectangle that is shorter can possibly be used to extend
  // a rectangle that is further away, which could result in a possibly larger
  // area.
  // E.g., 1 * 10 as opposed to 3 * 3
  // A taller rectangle's height is only useful for another equal, or taller
  // rectangle, and is useless when encountering a shorter rectangle.
  // Therefore, a monotonically non-decreasing stack will be useful.
  int largestRectangleArea(const std::vector<int>& heights) {
    const int n = heights.size();
    std::stack<int> stk;

    int best = 0;
    for (int i = 0; i < n; ++i) {
      while (!stk.empty() && heights[stk.top()] > heights[i]) {
        // this rectangle is the local maximum.
        // This means stack top can't extend to position i
        // Thus, we can be sure that a
        // rectangle to its right will only utilize part of this height.
        int height = heights[stk.top()];
        stk.pop();
        int left = stk.empty() ? -1 : stk.top();

        int width = i - 1 - left;
        best = std::max(best, height * width);
      }

      stk.push(i);
    }

    while (!stk.empty()) {
      int height = heights[stk.top()];
      stk.pop();
      int left = stk.empty() ? -1 : stk.top();

      // Width extends right to the end of the array.
      int width = n - 1 - left;
      best = std::max(best, height * width);
    }
    return best;
  }
};
