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
  int numIslands(std::vector<std::vector<char>>& grid) {
    // '1' represent land. '0' represent water. i.e. unreachable
    int m = grid.size();
    int n = grid[0].size();

    UnionFind uf(m * n + 1);  // add one to denote water set
    int WATER = m * n;

    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        int current = i * n + j;
        if (grid[i][j] == '0') {
          uf.unite(current, WATER);
          continue;
        }

        // Union with neighbouring land cells
        // Order of traversal mean with only need to check right and down
        if (j + 1 < n && grid[i][j + 1] == '1') {
          uf.unite(current, current + 1);
        }
        if (i + 1 < m && grid[i + 1][j] == '1') {
          uf.unite(current, current + n);
        }
      }
    }

    return uf.components() - 1;  // minus the WATER sentinel
  }

  int numIslandsNaive(std::vector<std::vector<char>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();

    UnionFind uf(rows * cols);

    // '1's are land, can traverse. '0's are water, cannot traverse.
    int waterCount = 0;
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        if (grid[i][j] == '0') {
          ++waterCount;
          continue;
        }

        int current = i * cols + j;  // map 2D coordinates to 1D line

        // Due to order of iteration: left-to-right, top-to-bottom,
        // only need to check two directions: right and down
        // Check right
        if (j < cols - 1 && grid[i][j + 1] == '1') {
          uf.unite(current, current + 1);
        }

        if (i < rows - 1 && grid[i + 1][j] == '1') {
          uf.unite(current, current + cols);
        }
      }
    }

    return uf.components() - waterCount;  // Each water cell is a disjoint set
  }
};
