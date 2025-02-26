#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <functional>
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
  int maxNumEdgesToRemove(int n, std::vector<std::vector<int>>& edges) {
    // Two Union Find?
    // Then, while uniting, skip edges that would connect already connected
    // components.
    // Check that the final number of components is exactly one.
    // Sort to use type 3 first.
    // Or rather, just iterate and unite type3 first.
    // Then settle type 1/2 in another loop
    // std::sort(edges.begin(), edges.end(), std::greater<>{});
    UnionFind Alice(n);
    UnionFind Bob(n);
    int skip = 0;
    for (const auto& edge : edges) {
      int type = edge[0], u = edge[1] - 1, v = edge[2] - 1;
      if (type == 3) {
        if (Alice.connected(u, v) && Bob.connected(u, v)) {
          ++skip;
        } else {
          Alice.unite(u, v);
          Bob.unite(u, v);
        }
      }
    }

    for (const auto& edge : edges) {
      int type = edge[0], u = edge[1] - 1, v = edge[2] - 1;

      if (type == 1) {
        if (Alice.connected(u, v)) {
          ++skip;
        } else {
          Alice.unite(u, v);
        }
      } else if (type == 2) {
        if (Bob.connected(u, v)) {
          ++skip;
        } else {
          Bob.unite(u, v);
        }
      }
    }

    if (Alice.components() != 1 || Bob.components() != 1) {
      return -1;
    }

    return skip;
  }
};
