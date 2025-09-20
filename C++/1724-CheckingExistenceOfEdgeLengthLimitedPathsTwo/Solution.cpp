#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <deque>
#include <functional>
#include <iostream>
#include <istream>
#include <iterator>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
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

class DistanceLimitedPathsExist {
 public:
  DistanceLimitedPathsExist(int n, std::vector<std::vector<int>>& edgeList)
      : G(n), componentMax(n, 0) {
    auto cmp = [](const auto& a, const auto& b) -> bool {
      if (a[2] < b[2]) {
        return true;
      }

      if (a[2] == b[2] && a[0] < b[0]) {
        return true;
      }

      if (a[2] == b[2] && a[0] == b[0] && a[1] < b[1]) {
        return true;
      }
      return false;
    };

    std::sort(edgeList.begin(), edgeList.end(), cmp);

    for (const auto& edge : edgeList) {
      int u = edge[0], v = edge[1], cost = edge[2];

      if (G.connected(u, v)) {
        continue;
      }

      int root1 = G.find(u);
      int root2 = G.find(v);

      // Need to be careful of roots changing, due to union-by-rank and
      // path-compression
      G.unite(u, v);
      int newRoot = G.find(u);
      componentMax[newRoot] =
          std::max({componentMax[root1], componentMax[root2], cost});
    }
  }

  bool query(int p, int q, int limit) {
    if (!G.connected(p, q)) {
      return false;
    }

    return componentMax[G.find(p)] < limit;
  }

 private:
  UnionFind G;
  std::vector<int> componentMax;
};

/**
 * Your DistanceLimitedPathsExist object will be instantiated and called as
 * such: DistanceLimitedPathsExist* obj = new DistanceLimitedPathsExist(n,
 * edgeList); bool param_1 = obj->query(p,q,limit);
 */
