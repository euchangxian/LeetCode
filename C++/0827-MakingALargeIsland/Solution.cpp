#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdlib>
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

  int maxSize() const { return *std::max_element(size_.begin(), size_.end()); }

 private:
  int components_;

  std::vector<int> parent_;
  std::vector<int> rank_;
  std::vector<int> size_;
};

constexpr std::array<std::array<int, 2>, 4> directions{{
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0},
}};

class Solution {
 public:
  int largestIsland(std::vector<std::vector<int>>& grid) {
    // O(n^3) is possible with n<=500
    // Union '1's to find the components, along with their sizes.
    // For remaining 0s, iterate through and check the cardinal sizes of
    // islands.
    // O(N^2).
    const int m = grid.size();
    const int n = grid[0].size();

    UnionFind G(m * n);
    std::vector<std::pair<int, int>> zeroPos;
    zeroPos.reserve(m * n);
    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        if (grid[r][c] == 0) {
          zeroPos.emplace_back(r, c);
        } else {
          int curr = r * n + c;

          if (c + 1 < n && grid[r][c + 1] == 1) {
            G.unite(curr, curr + 1);
          }
          if (r + 1 < m && grid[r + 1][c] == 1) {
            G.unite(curr, curr + n);
          }
        }
      }
    }

    std::vector<bool> seen(m * n);
    int maxIslandSize = 0;
    for (auto [r, c] : zeroPos) {
      std::fill(seen.begin(), seen.end(), false);
      int islandSize = 1;
      for (const auto [dr, dc] : directions) {
        int nr = r + dr;
        int nc = c + dc;
        if (nr < 0 || nc < 0 || nr >= m || nc >= n || grid[nr][nc] == 0 ||
            seen[G.find(nr * n + nc)]) {
          continue;
        }
        seen[G.find(nr * n + nc)] = true;
        islandSize += G.size(G.find(nr * n + nc));
      }

      maxIslandSize = std::max(maxIslandSize, islandSize);
    }

    return std::max(maxIslandSize, G.maxSize());
  }
};
