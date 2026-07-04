#include <algorithm>
#include <limits>
#include <numeric>
#include <vector>

class UnionFind {
 public:
  UnionFind(int n)
      : parent_(n), rank_(n, 0), distance_(n, std::numeric_limits<int>::max()) {
    std::iota(parent_.begin(), parent_.end(), 0);
  }

  int find(int x) noexcept {
    if (parent_[x] != x) {
      parent_[x] = find(parent_[x]);
    }

    return parent_[x];
  }

  bool connected(int x, int y) noexcept { return find(x) == find(y); }

  void unite(int x, int y, int distance) noexcept {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY) {
      distance_[rootX] = std::min(distance_[rootX], distance);
      return;
    }

    if (rank_[rootX] < rank_[rootY]) {
      parent_[rootX] = rootY;
      distance_[rootY] =
          std::min({distance_[rootX], distance_[rootY], distance});
      return;
    }

    if (rank_[rootX] == rank_[rootY]) {
      ++rank_[rootX];
    }
    parent_[rootY] = rootX;
    distance_[rootX] = std::min({distance_[rootX], distance_[rootY], distance});
  }

  auto distance(int x) noexcept { return distance_[find(x)]; }

 private:
  std::vector<int> parent_;
  std::vector<int> rank_;
  std::vector<int> distance_;
};

class Solution {
 public:
  int minScore(int n, std::vector<std::vector<int>>& roads) {
    // n cities
    // roads[i] = [a, b, distance] => bidirectional edge between a and b.
    // Score between two cities is the minimum distance of a road in the path.
    // Return the minimum possible score of a path between cities 1 and n.
    UnionFind uf(n);
    for (const auto& road : roads) {
      auto u = road[0] - 1;
      auto v = road[1] - 1;
      auto distance = road[2];
      uf.unite(u, v, distance);
    }

    return uf.distance(0);
  }
};
