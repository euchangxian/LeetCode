#include <unordered_set>
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
  int removeStones(std::vector<std::vector<int>>& stones) {
    if (stones.size() < 2) {
      return 0;
    }

    // 0 <= xi, yi <= 10^4
    UnionFind uf(MAX_XY * 2);
    for (const auto& stone : stones) {
      int r = stone[0];
      int c = stone[1];

      // Offset column index
      // This can be a little unintuitive, where the row index of a stone is
      // unioned with its column index. but this ensures that subsequent stones
      // with either the same row or column index are connected by an edge with
      // the inserted stone.
      uf.unite(r, c + MAX_XY);
    }

    std::unordered_set<int> uniqueRoots;
    for (const auto& stone : stones) {
      uniqueRoots.insert(uf.find(stone[0]));
    }

    return stones.size() - uniqueRoots.size();
  }

 private:
  const int MAX_XY = 10001;
};
