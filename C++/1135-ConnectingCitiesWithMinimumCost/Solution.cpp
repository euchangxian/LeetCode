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

 private:
  int components_;

  std::vector<int> parent_;
  std::vector<int> rank_;
  std::vector<int> size_;
};

class Solution {
 public:
  int minimumCost(int n, std::vector<std::vector<int>>& connections) {
    std::ranges::sort(connections, {},
                      [](const auto& edge) { return edge[2]; });

    int cost = 0;
    UnionFind G(n + 1);
    for (const auto& edge : connections) {
      int u = edge[0], v = edge[1], w = edge[2];

      if (!G.connected(u, v)) {
        G.unite(u, v);
        cost += w;
      }
    }

    // 1-indexed
    if (G.components() - 1 > 1) {
      return -1;
    }
    return cost;
  }
};
