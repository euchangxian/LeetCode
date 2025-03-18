#include <cstddef>
#include <vector>

/**
 * Similar to 1D; prefix sums are necessary for O(1) sumRegion.
 * Easier with the diagram.
 * Essentially, the prefix sums are the total sum of all the rows and columns
 * up to (i, j), inclusive.
 * Add an extra row/column to the left/top since the range sums are inclusive.
 */
class NumMatrix {
 private:
  std::vector<std::vector<int>> prefix;

 public:
  NumMatrix(std::vector<std::vector<int>>& matrix) {
    const std::size_t rows = matrix.size();
    const std::size_t cols = matrix[0].size();

    prefix =
        std::vector<std::vector<int>>(rows + 1, std::vector<int>(cols + 1, 0));
    for (std::size_t i = 1; i < rows + 1; ++i) {
      for (std::size_t j = 1; j < cols + 1; ++j) {
        prefix[i][j] = prefix[i - 1][j] +      // rectangle above
                       prefix[i][j - 1] +      // rectangle to the left
                       matrix[i - 1][j - 1] -  // current cell
                       prefix[i - 1][j - 1];   // double counted region
      }
    }
  }

  int sumRegion(int row1, int col1, int row2, int col2) {
    // Note that there will be double-minusing of a region at the top left
    // area
    return prefix[row2 + 1][col2 + 1] -
           prefix[row1][col2 + 1] -  // rectangle above desired region
           prefix[row2 + 1][col1] +  // rectangle to the left
           prefix[row1][col1];       // add the double-counted/overlap region
  }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */
