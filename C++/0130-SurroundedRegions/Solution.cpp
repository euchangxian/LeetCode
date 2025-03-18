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

constexpr std::array<std::array<int, 2>, 4> directions{{
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0},
}};

class Solution {
 public:
  void solve(std::vector<std::vector<char>>& board) {
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
        for (const auto [rDir, cDir] : directions) {
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
