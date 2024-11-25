#include <array>
#include <queue>
#include <unordered_set>

class Solution {
 private:
  static constexpr int BOARD_SIZE = 6;
  using Board = std::array<int, BOARD_SIZE>;

  static constexpr Board target{1, 2, 3, 4, 5, 0};

  static constexpr std::array<int, 4> dr{0, 1, 0, -1};
  static constexpr std::array<int, 4> dc{1, 0, -1, 0};

  static constexpr int toIndex(int r, int c) {
    return r * 3 + c;  // 3 is board width
  }

  static constexpr std::pair<int, int> toCoord(int idx) {
    return {idx / 3, idx % 3};
  }

  static constexpr bool isValid(int r, int c) {
    return (r >= 0 && r < 2) && (c >= 0 && c < 3);  // 2x3 board
  }

  // Convert board to unique integer for hashing
  static int encode(const Board& board) {
    int code = 0;
    for (int i = 0; i < BOARD_SIZE; ++i) {
      code = code * 10 + board[i];
    }
    return code;
  }

  static bool isTarget(const Board& board) { return board == target; }

 public:
  int slidingPuzzle(std::vector<std::vector<int>>& board) {
    // Convert 2D board to 1D representation
    Board initial;
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 3; ++j) {
        initial[toIndex(i, j)] = board[i][j];
      }
    }

    std::queue<Board> frontier;
    std::unordered_set<int> seen;

    frontier.push(initial);
    seen.insert(encode(initial));

    int steps = 0;
    while (!frontier.empty()) {
      for (int size = frontier.size(); size > 0; --size) {
        Board current = frontier.front();
        frontier.pop();

        if (isTarget(current)) {
          return steps;
        }

        // Find empty tile
        int zeroIdx = std::distance(
            current.begin(), std::find(current.begin(), current.end(), 0));
        auto [zr, zc] = toCoord(zeroIdx);

        // Try all possible moves in cardinal directions
        for (int i = 0; i < 4; ++i) {
          int nr = zr + dr[i];
          int nc = zc + dc[i];

          if (!isValid(nr, nc)) {
            continue;
          }

          Board next = current;
          std::swap(next[zeroIdx], next[toIndex(nr, nc)]);

          int encodedNext = encode(next);
          if (seen.insert(encodedNext).second) {
            frontier.push(std::move(next));
          }
        }
      }
      ++steps;
    }

    return -1;
  }
};

