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
  int countCompleteComponents(int n, std::vector<std::vector<int>>& edges) {
    UnionFind uf(n);

    std::vector<int> edgeCount(n, 0);
    for (const auto& edge : edges) {
      uf.unite(edge[0], edge[1]);

      ++edgeCount[edge[0]];
      ++edgeCount[edge[1]];
    }

    std::vector<bool> isComplete(n, true);
    for (int i = 0; i < n; ++i) {
      int root = uf.find(i);

      int componentSize = uf.size(root);

      // For a component to be complete, each node must have v-1 edges
      if (edgeCount[i] < componentSize - 1) {
        isComplete[root] = false;
      }
    }

    int result = 0;
    for (int i = 0; i < n; ++i) {
      // if root and complete
      if (uf.find(i) == i && isComplete[i]) {
        ++result;
      }
    }

    return result;
  }
};
