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
  std::vector<int> maxPoints(std::vector<std::vector<int>>& grid,
                             std::vector<int>& queries) {
    // Reworded, answer[i] is the number of cells reachable from (0, 0), and
    // is strictly less than queries[i].
    // Sort queries in increasing order. Union cells.
    // Hm, but traversing the grid every time to find cells less than queries[i]
    // is not cheap.
    // Maybe a PQ? Ordered by grid value.
    // Start with a Sentinel REACHABLE.
    // Then, if grid(0,0) is strictly less than query[i], unite it with
    // the sentinel.
    // Do a DFS uniting cardinal blocks. (or add them into the PQ).
    const int m = grid.size();
    const int n = grid[0].size();
    std::vector<std::pair<int, int>> sorted;
    sorted.reserve(queries.size());
    for (int i = 0; i < queries.size(); ++i) {
      sorted.emplace_back(queries[i], i);
    }
    std::sort(sorted.begin(), sorted.end());

    std::vector<std::pair<int, int>> points;
    points.reserve(m * n);
    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        points.emplace_back(grid[r][c], r * n + c);
      }
    }
    std::sort(points.begin(), points.end());

    UnionFind G(m * n);
    auto it = points.begin();
    std::vector<int> answer(queries.size(), 0);
    for (const auto [x, originalIdx] : sorted) {
      for (; it != points.end() && (*it).first < x; ++it) {
        // unite with cardinal directions, if they are less than x.
        const auto [y, j] = *it;
        const int r = j / n;
        const int c = j % n;

        for (const auto [dr, dc] : directions) {
          const int nr = r + dr;
          const int nc = c + dc;

          if (nr < 0 || nr >= m || nc < 0 || nc >= n || grid[nr][nc] >= x) {
            continue;
          }

          G.unite(j, nr * n + nc);
        }
      }

      if (grid[0][0] < x) {
        answer[originalIdx] = G.size(0);
      }
    }
    return answer;
  }
};
