#include <algorithm>
#include <cstddef>
#include <vector>

using namespace std;
class Solution {
 private:
  // Knights move in L shapes.
  static constexpr std::array<std::pair<int, int>, 8> directions{{
      {-2, -1},
      {-2, 1},  // Up 2, left/right 1
      {2, -1},
      {2, 1},  // Down 2, left/right 1
      {-1, -2},
      {1, -2},  // Left 2, up/down 1
      {-1, 2},
      {1, 2}  // Right 2, up/down 1
  }};

  bool dfs(std::vector<std::vector<int>>& board, int r, int c, int moveCount) {
    if (moveCount >= board.size() * board[0].size()) {
      return true;  // valid path.
    }

    for (const auto& [dr, dc] : directions) {
      const int nr = r + dr;
      const int nc = c + dc;

      if (nr < 0 || nc < 0 || nr >= board.size() || nc >= board[0].size() ||
          board[nr][nc] >= 0) {
        continue;
      }

      board[nr][nc] = moveCount;  // mark as visited
      bool hasTour = dfs(board, nr, nc, moveCount + 1);
      if (hasTour) {
        // Stop altering the grid.
        return true;
      }
      board[nr][nc] = -1;  // backtrack.
    }

    return false;
  }

 public:
  vector<vector<int>> tourOfKnight(int m, int n, int r, int c) {
    // First glance seems like a Graph problem. Not an Euler's tour/circuit,
    // since its not all edges that need to be traversed, but all nodes.
    // Forgot what's its name.
    // Right, Hamiltonian Path. Visit all nodes exactly once, end anywhere.
    // Though this is an NP-hard problem IIRC. Explains the small input sizes,
    // 1 <= m, n <= 5, lol.
    // Therefore, this is probably a backtracking problem.
    // DFS and check if the visited.size is equal to n * m. Otherwise,
    // backtrack.

    // Board in which the cells' values show the order of visiting the cell
    // starting from 0.
    // Use -1 to denote not visited.
    std::vector<std::vector<int>> board(m, std::vector<int>(n, -1));
    board[r][c] = 0;

    // Question guarantees the existence of at least one possible order of
    // movements.
    dfs(board, r, c, 1);

    return board;
  }
};
