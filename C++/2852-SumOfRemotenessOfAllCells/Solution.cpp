#include <cstddef>
#include <cstdlib>
#include <vector>

class UnionFind {
 public:
  UnionFind(int n) : parent(n), rank(n, 0), components(n) {
    for (int i = 0; i < n; ++i) {
      parent[i] = i;
    }
  }

  int find(int x) {
    if (parent[x] != x) {
      parent[x] = find(parent[x]);
    }

    return parent[x];
  }

  bool connected(int x, int y) { return find(x) == find(y); }

  void unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY) {
      return;
    }

    --components;
    if (rank[rootX] < rank[rootY]) {
      parent[rootX] = rootY;
      return;
    }

    if (rank[rootX] == rank[rootY]) {
      ++rank[rootX];
    }
    parent[rootY] = rootX;
  }

  int size() const { return components; }

 private:
  int components;

  std::vector<int> parent;
  std::vector<int> rank;
};

using i64 = long long;
class Solution {
 public:
  i64 sumRemoteness(std::vector<std::vector<int>>& grid) {
    // grid[i][j] == -1 | > 0
    // -1 => blocked
    //
    // remoteness[i][j]:
    // - if grid[i][j] is not blocked, then remoteness[i][j] is the sum of
    //   values of grid[x][y] such that there is no path from (x, y) to (i, j).
    //   i.e., both (i, j) and (x, y) are in different components/islands.
    // - if blocked, then remoteness[i][j] = 0.
    //
    // Naively, UnionFind to group components. One pass
    // Then,    Sum of each component, and total sum too. Second pass.
    // Then,    Assign Remoteness values, Total - component. Third pass.
    // Finally, Sum up remoteness values. Fourth Pass.
    const int n = grid.size();
    UnionFind G(n * n);
    i64 total = 0LL;
    for (int r = 0; r < n; ++r) {
      for (int c = 0; c < n; ++c) {
        int curr = r * n + c;
        if (grid[r][c] == -1) {
          continue;
        }

        // order of iteration means that we only need to check right and bottom.
        if (c + 1 < n && grid[r][c + 1] != -1) {
          G.unite(curr, curr + 1);
        }

        if (r + 1 < n && grid[r + 1][c] != -1) {
          G.unite(curr, curr + n);
        }

        total += grid[r][c];
      }
    }

    std::vector<i64> componentSum(n * n, 0LL);
    for (int r = 0; r < n; ++r) {
      for (int c = 0; c < n; ++c) {
        if (grid[r][c] == -1) {
          continue;
        }
        int curr = r * n + c;
        componentSum[G.find(curr)] += grid[r][c];
      }
    }

    i64 remotenessSum = 0LL;
    for (int r = 0; r < n; ++r) {
      for (int c = 0; c < n; ++c) {
        if (grid[r][c] == -1) {
          continue;
        }
        int curr = r * n + c;
        remotenessSum += total - componentSum[G.find(curr)];
      }
    }

    return remotenessSum;
  }
};
