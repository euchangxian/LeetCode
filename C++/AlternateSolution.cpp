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
  int components;

public:
  UnionFind(int n) : parent(n), rank(n), components(n) {
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
      return; // already in same component
    }
    // Check rank
    if (rank[rootX] < rank[rootY]) {
      parent[rootX] = parent[rootY];
    } else {
      if (rank[rootX] == rank[rootY]) {
        ++rank[rootX];
      }
      parent[rootY] = parent[rootX];
    }
    --components;
  }

  int size() { return components; }
};
class Solution {
public:
  int numIslands(vector<vector<char>> &grid) {
    // '1' represent land. '0' represent water. i.e. unreachable
    int m = grid.size();
    int n = grid[0].size();

    UnionFind uf(m * n + 1); // add one to denote water set
    int WATER = m * n;

    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        int current = i * n + j;
        if (grid[i][j] == '0') {
          uf.unite(current, WATER);
          continue;
        }

        // Union with neighbouring land cells
        // Order of traversal mean with only need to check right and down
        if (j + 1 < n && grid[i][j + 1] == '1') {
          uf.unite(current, current + 1);
        }
        if (i + 1 < m && grid[i + 1][j] == '1') {
          uf.unite(current, current + n);
        }
      }
    }

    return uf.size() - 1; // minus the water component
  }
};
