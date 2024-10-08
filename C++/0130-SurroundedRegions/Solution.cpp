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

 public:
  UnionFind(int size) : parent(size), rank(size) {
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

  bool connected(int x, int y) { return find(x) == find(y); }

  void unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY) {
      return;
    }

    if (rank[rootX] < rank[rootY]) {
      parent[rootX] = parent[rootY];
      return;
    }

    if (rank[rootX] == rank[rootY]) {
      ++rank[rootX];
    }
    parent[rootY] = parent[rootX];
  }
};

class Solution {
 private:
  // right, down, left, up
  const vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

 public:
  void solve(vector<vector<char>>& board) {
    int m = board.size();
    int n = board[0].size();

    // The tricky part is determining that a region of 'O' is surrounded by
    // 'X's.
    // Observe that 'O's will not be surrounded if they are connected to an
    // 'O' on the edges of the board.
    // Therefore, for every region, check if it, and any 'O's on the boundaries
    // are in the same disjoint set. To prevent iterating over the entire set of
    // 'O's on the edges, assign an arbitrary parent.

    int cannotFlip = m * n;
    UnionFind uf(m * n + 1);  // Last position for cannotFlip
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (board[i][j] == 'X') {
          continue;
        }

        int current = i * n + j;  // Map 2D to its 1D representation

        // Check if its a boundary 'O'
        if (i == 0 || i == m - 1 || j == 0 || j == n - 1) {
          uf.unite(current, cannotFlip);
          continue;
        }

        // Union with surrounding O's
        for (const auto& [rDir, cDir] : directions) {
          int nr = i + rDir;
          int nc = j + cDir;

          if (nr < 0 || nr >= m || nc < 0 || nc >= n || board[nr][nc] != 'O') {
            continue;
          }
          uf.unite(current, nr * n + nc);
        }
      }
    }

    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (!uf.connected(cannotFlip, uf.find(i * n + j))) {
          board[i][j] = 'X';
        }
      }
    }

    return;
  }
};
