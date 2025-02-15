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

class Solution {
 public:
  std::vector<int> numIslands2(int m,
                               int n,
                               std::vector<std::vector<int>>& positions) {
    // empty 2D binary grid of m*n.
    // 0s represent water, 1s represent land. Initially all water.
    // positions[i] = {r, c} represents the ith operation that turns the cell
    // at (r, c) into a land cell.
    // Return answers[i] representing the number of islands after turning the
    // cell into a land.
    // Seems to be a simple variant of UF.
    // Start with all disjoint components indicating water.
    // When adding positions[i] = {r, c}, unite it with all adjacent LAND cells.
    // Determine the number of components remaining.
    UnionFind G(m * n);  // all water

    // is land, not island! >_<
    std::vector<bool> isLand(m * n, false);

    int water = m * n;
    std::vector<int> answers;
    answers.reserve(positions.size());
    for (const auto& query : positions) {
      int r = query[0], c = query[1];
      int idx = r * n + c;  // convert to 1D.
      if (isLand[idx] == true) {
        // skip duplicate queries
        answers.push_back(G.components() - water);
        continue;
      }
      isLand[idx] = true;
      --water;  // to assist with counting components

      // check cardinal directions. right, down, left, up.
      // right
      if (c + 1 < n && isLand[idx + 1]) {
        G.unite(idx, idx + 1);
      }

      // down
      if (r + 1 < m && isLand[idx + n]) {
        G.unite(idx, idx + n);
      }

      // left
      if (c - 1 >= 0 && isLand[idx - 1]) {
        G.unite(idx, idx - 1);
      }

      // up
      if (r - 1 >= 0 && isLand[idx - n]) {
        G.unite(idx, idx - n);
      }

      answers.push_back(G.components() - water);
    }
    return answers;
  }
};
