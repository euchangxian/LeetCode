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
  UnionFind(int size) : parent(size), rank(size), components(size) {
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

  void unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY) {
      return;
    }

    --components;
    if (rank[rootX] < rank[rootY]) {
      parent[rootX] = parent[rootY];
      return;
    }

    parent[rootY] = parent[rootX];
    if (rank[rootX] == rank[rootY]) {
      ++rank[rootX];
    }
  }

  int size() { return components; }
};
class Solution {
public:
  int countSubIslands(vector<vector<int>> &grid1, vector<vector<int>> &grid2) {
    // Intuition. For each land cell in grid2, begin DFS. A cell is considered a
    // neighbour iff it is a land cell in grid 2 AND in grid1. Count components.
    int rows = grid2.size();
    int cols = grid2[0].size();

    // Start with r * c components, each cell is its own component
    // Add one more component. All non-subislands will be union-ed with this
    int NOT_SUBISLAND = rows * cols;
    UnionFind uf(rows * cols + 1);

    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        int curr = i * cols + j;
        if (grid2[i][j] == 0) {
          // If water cell, unite and continue
          uf.unite(curr, NOT_SUBISLAND);
          continue;
        }

        if (grid1[i][j] == 0) {
          // if landcell, but not contained in grid1, unite with the
          // NOT_SUBISLAND component
          // It is important to not skip checking neighbours to ensure
          // islands in grid2 are still properly grouped together
          uf.unite(curr, NOT_SUBISLAND);
        }

        // Check bottom cell
        if (i + 1 < rows && grid2[i + 1][j] == 1) {
          uf.unite(curr, curr + cols);
        }

        // Check right cell
        if (j + 1 < cols && grid2[i][j + 1] == 1) {
          uf.unite(curr, curr + 1);
        }
      }
    }

    return uf.size() - 1;
  }
};
