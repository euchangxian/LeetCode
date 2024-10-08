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
  int sets;

 public:
  UnionFind(int size) : parent(size), rank(size, 0), sets(size) {
    for (int i = 0; i < size; ++i) {
      parent[i] = i;
    }
  }

  int find(int x) {
    if (parent[x] != x) {
      parent[x] = find(parent[x]);
    }
    return parent[x];
  }

  bool isConnected(int x, int y) { return find(x) == find(y); }

  void unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    // weighted union
    if (rootX != rootY) {
      if (rank[rootX] < rank[rootY]) {
        parent[rootX] = parent[rootY];
      } else if (rank[rootY] < rank[rootX]) {
        parent[rootY] = parent[rootX];
      } else {
        parent[rootY] = parent[rootX];
        ++rank[rootX];
      }
      --sets;
    }
  }

  int size() { return sets; }
};

class Solution {
 public:
  int numIslands(vector<vector<char>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();

    UnionFind uf(rows * cols);

    // '1's are land, can traverse. '0's are water, cannot traverse.
    int waterCount = 0;
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        if (grid[i][j] == '0') {
          ++waterCount;
          continue;
        }

        int current = i * cols + j;  // map 2D coordinates to 1D line

        // Due to order of iteration: left-to-right, top-to-bottom,
        // only need to check two directions: right and down
        // Check right
        if (j < cols - 1 && grid[i][j + 1] == '1') {
          uf.unionSets(current, current + 1);
        }

        if (i < rows - 1 && grid[i + 1][j] == '1') {
          uf.unionSets(current, current + cols);
        }
      }
    }

    return uf.size() - waterCount;  // Each water cell is a disjoint set
  }
};
