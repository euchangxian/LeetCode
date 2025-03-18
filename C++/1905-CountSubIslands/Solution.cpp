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

 private:
  int components_;

  std::vector<int> parent_;
  std::vector<int> rank_;
  std::vector<int> size_;
};

class Solution {
 public:
  int countSubIslands(std::vector<std::vector<int>>& grid1,
                      std::vector<std::vector<int>>& grid2) {
    // Intuition. For each land cell in grid2, begin DFS. A cell is considered a
    // neighbour iff it is a land cell in grid 2 AND in grid1. Count components.
    int rows = grid2.size();
    int cols = grid2[0].size();

    // Start with r * c components, each cell is its own component
    // Add one more component. All non-subislands will be union-ed with this
    int NOT_SUBISLAND = rows * cols;
    UnionFind uf(rows * cols + 1);

    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        int curr = i * cols + j;
        if (grid2[i][j] == 0) {
          // If water cell, unite and continue
          uf.unite(curr, NOT_SUBISLAND);
          continue;
        }

        if (grid1[i][j] == 0) {
          // if landcell, but not contained in grid1, unite with the
          // NOT_SUBISLAND component
          // It is important to not skip checking neighbours to ensure
          // islands in grid2 are still properly grouped together
          uf.unite(curr, NOT_SUBISLAND);
        }

        // Check bottom cell
        if (i + 1 < rows && grid2[i + 1][j] == 1) {
          uf.unite(curr, curr + cols);
        }

        // Check right cell
        if (j + 1 < cols && grid2[i][j + 1] == 1) {
          uf.unite(curr, curr + 1);
        }
      }
    }

    return uf.components() - 1;
  }
};
