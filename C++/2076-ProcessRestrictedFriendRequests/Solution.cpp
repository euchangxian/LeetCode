#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstdint>
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

class Solution {
 public:
  std::vector<bool> friendRequests(int n,
                                   std::vector<std::vector<int>>& restrictions,
                                   std::vector<std::vector<int>>& requests) {
    // Naively, each time we attempt to unite (u, v), we check the
    // restricted neighbours of u and v.
    UnionFind G(n);

    std::vector<bool> answer;
    answer.reserve(requests.size());
    for (const auto& query : requests) {
      int u = query[0], v = query[1];
      int pu = G.find(u), pv = G.find(v);

      bool possible = true;

      if (!G.connected(u, v)) {
        for (const auto& restricted : restrictions) {
          int px = G.find(restricted[0]), py = G.find(restricted[1]);

          if ((pu == px && pv == py) || (pu == py && pv == px)) {
            possible = false;
            break;
          }
        }
      }

      if (possible) {
        G.unite(u, v);
      }
      answer.push_back(possible);
    }
    return answer;
  }
};
