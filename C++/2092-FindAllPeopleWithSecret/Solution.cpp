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

  void reset(int x) {
    parent_[x] = x;
    rank_[x] = 0;
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
  std::vector<int> findAllPeople(int n,
                                 std::vector<std::vector<int>>& meetings,
                                 int firstPerson) {
    // Sort by ascending time.
    // Union. Get all people in the same component as P0 and P1
    // Ah. Need to aggregate meetings that happen at the same time.
    UnionFind G(n + 1);
    G.unite(0, firstPerson);

    std::ranges::sort(meetings, {}, [](const auto& vec) { return vec[2]; });

    std::vector<int> sameTime;
    int i = 0;
    while (i < meetings.size()) {
      sameTime.clear();
      int time = meetings[i][2];
      while (i < meetings.size() && meetings[i][2] == time) {
        int u = meetings[i][0], v = meetings[i][1];
        ++i;

        G.unite(u, v);

        sameTime.push_back(u);
        sameTime.push_back(v);
      }

      for (int x : sameTime) {
        if (!G.connected(0, x)) {
          G.reset(x);
        }
      }
    }

    std::vector<int> hasSecret;
    hasSecret.reserve(n);
    hasSecret.push_back(0);
    for (int i = 1; i < n; ++i) {
      if (G.connected(0, i)) {
        hasSecret.push_back(i);
      }
    }
    return hasSecret;
  }
};
