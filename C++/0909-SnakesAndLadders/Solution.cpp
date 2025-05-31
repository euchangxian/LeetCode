#include <algorithm>
#include <queue>
#include <utility>
#include <vector>

constexpr int INF = 1000;
class Solution {
 public:
  int snakesAndLadders(std::vector<std::vector<int>>& board) {
    // n x n board, labelled [1..n^2] in Boustrophedon style.
    // i.e., from bottom left:
    // --> 7 8 9
    // <-- 6 5 4
    // --> 1 2 3
    // Start on cell 1.
    // At each cell x:
    // - Choose a destination square next, in the range [x+1, min(x+6, n^2)]
    //   i.e., a 6-sided dice roll.
    // - if next has a snake or ladder, move to the destination of the
    //   snake/ladder. Otherwise, move to next.
    // Ends when cell n^2 is reached.
    // if board[r][c] != -1, then there is a snake/ladder to board[r][c].
    // Return the least number of dice rolls required to reach square n^2, or
    // -1.
    //
    // Hm. A snake is not always unoptimal. A ladder is not always optimal.
    // 2 <= n <= 20 ==> 4 <= n^2 <= 400
    // Naive backtracking is not possible. Worst case is a snake/ladder at
    // every cell.
    // Hm. Just BFS. Lol. Add a new node if there is a ladder/snake.
    const int n = board.size();
    const int nSquare = n * n;

    auto toCoords = [&](int x) -> std::pair<int, int> {
      --x;
      int row = x / n;  // from the bottom. But boards is given in "reverse"
      int col = x % n;  // to determine direction
      if (row % 2) {
        col = n - 1 - col;
      }
      return std::make_pair(n - 1 - row, col);
    };

    std::vector<int> dist(n * n + 1, -1);
    std::queue<int> frontier;
    frontier.emplace(1);
    dist[1] = 0;
    while (!frontier.empty()) {
      int curr = frontier.front();
      frontier.pop();

      for (int next = curr + 1; next <= std::min(curr + 6, nSquare); ++next) {
        auto [nr, nc] = toCoords(next);
        int destination = board[nr][nc] == -1 ? next : board[nr][nc];
        if (dist[destination] != -1) {
          // visited.
          continue;
        }
        dist[destination] = dist[curr] + 1;
        frontier.emplace(destination);
      }
    }
    return dist[nSquare];
  }
};
