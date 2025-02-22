#include <array>
#include <cstddef>
#include <cstdlib>
#include <ranges>
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

constexpr std::array<std::array<int, 2>, 4> directions{{
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0},
}};

class Solution {
 public:
  int latestDayToCross(int row, int col, std::vector<std::vector<int>>& cells) {
    // 1-based binary matrix size rows * cols
    // cells[i] = [r, c] indicate the (r, c) cell which will be changed into a
    // water cell on the ith day.
    // Not so straightforward to union, since we need to ensure that there is
    // a path from top to bottom.
    // What about treating each row as a component, instead of each cell?
    // So if the top and bottom are in the same component, then there is a path?
    // Nope. Not so straightforward. E.g.,:
    // 0 1 1
    // 0 1 0
    // 1 1 0
    // The union would wrongly determine that top to bottom is connected, but
    // there is actually no path.
    // What about using sentinels, TOP and BOTTOM, where each cell is initially
    // its own connected component.
    // Then, start by unioning all Land cells in the top to the TOP sentinel,
    // and bottom respectively.
    // Unite all Land cells to their cardinal land cells. Then, if there is a
    // path from top to bottom, the two sentinels should be connected via
    // transitive closure.

    // grid[r][c] = 0 | 1, 1 indicate water.
    std::vector<std::vector<bool>> water(row, std::vector<bool>(col, 1));
    const int TOP = row * col;
    const int BOTTOM = row * col + 1;
    UnionFind G(row * col + 2);

    int lastDay = cells.size();
    for (const auto& cell : cells | std::ranges::views::reverse) {
      if (G.connected(TOP, BOTTOM)) {
        break;
      }
      --lastDay;

      int r = cell[0] - 1, c = cell[1] - 1;
      water[r][c] = 0;

      int idx = r * col + c;
      if (r == 0) {
        G.unite(TOP, idx);
      }
      if (r == row - 1) {
        G.unite(BOTTOM, idx);
      }

      for (const auto [dr, dc] : directions) {
        int nr = r + dr;
        int nc = c + dc;

        if (nr < 0 || nc < 0 || nr >= row || nc >= col || water[nr][nc]) {
          continue;
        }

        G.unite(idx, nr * col + nc);
      }
    }
    return lastDay;
  }
};
