#include <vector>

class Solution {
 public:
  std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    std::vector<int> result;
    result.reserve(rows * cols);

    // Define the boundaries. To stop traversing when the bounds are reached
    int top = 0, bottom = rows - 1, left = 0, right = cols - 1;
    while (top <= bottom && left <= right) {
      // Traverse top row left-to-right
      for (int col = left; col <= right; ++col) {
        result.push_back(matrix[top][col]);
      }
      ++top;

      // Traverse right column top-to-bottom
      for (int row = top; row <= bottom; ++row) {
        result.push_back(matrix[row][right]);
      }
      --right;

      // Traverse bottom row right-to-left
      // Handle the case where there is only a single row first, preventing
      // double-counting
      if (top <= bottom) {
        for (int col = right; col >= left; --col) {
          result.push_back(matrix[bottom][col]);
        }
        --bottom;
      }

      // Traverse left column bottom-to-top
      // Handle the case where there is a single column left
      if (left <= right) {
        for (int row = bottom; row >= top; --row) {
          result.push_back(matrix[row][left]);
        }
        ++left;
      }
    }

    return result;
  }
};
