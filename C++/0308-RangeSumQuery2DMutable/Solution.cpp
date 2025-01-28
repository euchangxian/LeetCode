#include <cstddef>
#include <cstdlib>
#include <utility>
#include <vector>

class FenwickTree {
 public:
  FenwickTree(const std::vector<std::vector<int>>& matrix)
      : M(matrix.size()),
        N(matrix[0].size()),
        tree_(M + 1, std::vector<int>(N + 1, 0)) {
    for (int r = 1; r <= M; ++r) {
      for (int c = 1; c <= N; ++c) {
        update(r, c, matrix[r - 1][c - 1]);
      }
    }
  }

  // Visualizing the rectangle sum calculation:
  //
  // We want area D. Using inclusion-exclusion:
  // D = query(r2,c2) - A - B + C
  //
  //         +---------+----------+
  //         |    C    |     A    |
  //         | (r1, c1)|          |
  //         +---------+----------+
  //         |    B    |     D    |
  //         |         |          |
  //         +---------+----------+ (r2,c2)
  //
  // Where:
  // - query(r2,c2)     = A + B + C + D  (full rectangle)
  // - query(r2,c1-1)   = B + C          (left rectangle)
  // - query(r1-1,c2)   = A + C          (top rectangle)
  // - query(r1-1,c1-1) = C              (top-left rectangle)
  //
  // Therefore:
  // D = (A + B + C + D) - (B + C) - (A + C) + C
  int query(int r1, int c1, int r2, int c2) const {
    return query(r2, c2) - query(r2, c1 - 1) - query(r1 - 1, c2) +
           query(r1 - 1, c1 - 1);
  }

  void update(int r, int c, int diff) {
    for (int i = r; i <= M; i += (i & -i)) {
      for (int j = c; j <= N; j += (j & -j)) {
        tree_[i][j] += diff;
      }
    }
  }

 private:
  const int M;
  const int N;
  std::vector<std::vector<int>> tree_;

  // sum of rectangle from (1, 1) to (r, c);
  int query(int r, int c) const {
    int sum = 0;

    for (int i = r; i > 0; i -= (i & -i)) {
      for (int j = c; j > 0; j -= (j & -j)) {
        sum += tree_[i][j];
      }
    }
    return sum;
  }
};

// 2D fenwick trees will work.
class NumMatrix {
 public:
  NumMatrix(std::vector<std::vector<int>>& matrix)
      : matrix_(std::move(matrix)), ft_(matrix_) {}

  void update(int row, int col, int val) {
    int diff = val - std::exchange(matrix_[row][col], val);
    ft_.update(row + 1, col + 1, diff);
  }

  int sumRegion(int row1, int col1, int row2, int col2) {
    return ft_.query(row1 + 1, col1 + 1, row2 + 1, col2 + 1);
  }

 private:
  std::vector<std::vector<int>> matrix_;
  FenwickTree ft_;
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * obj->update(row,col,val);
 * int param_2 = obj->sumRegion(row1,col1,row2,col2);
 */
