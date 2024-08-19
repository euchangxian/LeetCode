#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class UnionFind {
private:
  vector<int> parent;
  vector<int> rank;
  vector<int> size;

public:
  UnionFind(int n) : parent(n), rank(n), size(n, 1) {
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

    if (rank[rootX] < rank[rootY]) {
      parent[rootX] = parent[rootY];
      size[rootY] += size[rootX];
    } else {
      if (rank[rootX] == rank[rootY]) {
        ++rank[rootX];
      }

      parent[rootY] = parent[rootX];
      size[rootX] += size[rootY];
    }
  }

  int maxComponentSize() { return *max_element(size.begin(), size.end()); }
};

class Solution {
public:
  int maxAreaOfIsland(vector<vector<int>> &grid) {
    int rows = grid.size();
    int cols = grid[0].size();

    UnionFind uf(rows * cols);
    bool hasLandCells = false; // Handle edge case
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        if (grid[i][j] == 0) {
          continue;
        }

        hasLandCells = true;

        int current = i * cols + j;
        // Check right and down
        if (j + 1 < cols && grid[i][j + 1] == 1) {
          uf.unite(current, current + 1);
        }
        if (i + 1 < rows && grid[i + 1][j] == 1) {
          uf.unite(current, current + cols);
        }
      }
    }

    return hasLandCells ? uf.maxComponentSize() : 0;
  }
};
