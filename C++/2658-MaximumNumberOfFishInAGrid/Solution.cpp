#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <utility>
#include <vector>

class UnionFind {
 public:
  UnionFind(const std::vector<std::vector<int>>& grid, int n)
      : components_(n), parent_(n), rank_(n, 0), size_(n) {
    const int col = grid[0].size();
    for (int i = 0; i < n; ++i) {
      parent_[i] = i;
      size_[i] = grid[i / col][i % col];
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

  int maxSize() const { return *std::max_element(size_.begin(), size_.end()); };

 private:
  int components_;

  std::vector<int> parent_;
  std::vector<int> rank_;
  std::vector<int> size_;
};

class Solution {
 public:
  int findMaxFish(std::vector<std::vector<int>>& grid) {
    // grid[r][c] = 0 => land cell.
    //            > 0 => water cell containing grid[r][c] fish.
    // Start at any cell (r, c), do any number of times:
    // - Catch all the fish at (r, c), or
    // - Move to any adjacent water cell.
    // Essentially, find the greatest sum of each component. UF.
    // Can be augmented to do a single pass too. But two pass is fine.
    const int m = grid.size();
    const int n = grid[0].size();

    UnionFind uf(grid, m * n);
    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        if (grid[r][c] == 0) {
          continue;
        }

        int curr = r * n + c;
        // unite with right and bottom, if the cells are WATER cells.
        if (c + 1 < n && grid[r][c + 1] > 0) {
          uf.unite(curr, curr + 1);
        }

        if (r + 1 < m && grid[r + 1][c] > 0) {
          uf.unite(curr, curr + n);
        }
      }
    }

    return uf.maxSize();
  }
};
