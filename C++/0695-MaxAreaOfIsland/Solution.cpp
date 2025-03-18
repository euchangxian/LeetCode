#include <algorithm>
#include <utility>
#include <vector>

class UnionFind {
 public:
  UnionFind(int n) : components_(n), parent_(n), rank_(n, 0), size_(n, 1) {
    for (int i = 0; i < n; ++i) {
      parent_[i] = i;
    }
  }

  int find(int x) {
    if (parent_[x] != x) {
      parent_[x] = find(parent_[x]);
    }

    return parent_[x];
  }

  bool connected(int x, int y) { return find(x) == find(y); }

  void unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY) {
      return;
    }

    --components_;
    if (rank_[rootX] < rank_[rootY]) {
      parent_[rootX] = rootY;
      size_[rootY] += std::exchange(size_[rootX], 0);
      return;
    }

    if (rank_[rootX] == rank_[rootY]) {
      ++rank_[rootX];
    }
    parent_[rootY] = rootX;
    size_[rootX] += std::exchange(size_[rootY], 0);
  }

  int components() const noexcept { return components_; }

  int size(int x) { return size_[find(x)]; }

  int maxComponentSize() {
    return *std::max_element(size_.begin(), size_.end());
  }

 private:
  int components_;

  std::vector<int> parent_;
  std::vector<int> rank_;
  std::vector<int> size_;
};

class Solution {
 public:
  int maxAreaOfIsland(std::vector<std::vector<int>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();

    UnionFind uf(rows * cols);
    bool hasLandCells = false;  // Handle edge case
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        if (grid[i][j] == 0) {
          continue;
        }

        hasLandCells = true;

        int current = i * cols + j;
        // Check right and down
        if (j + 1 < cols && grid[i][j + 1] == 1) {
          uf.unite(current, current + 1);
        }
        if (i + 1 < rows && grid[i + 1][j] == 1) {
          uf.unite(current, current + cols);
        }
      }
    }

    return hasLandCells ? uf.maxComponentSize() : 0;
  }
};
