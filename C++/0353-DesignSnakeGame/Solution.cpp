#include <array>
#include <deque>
#include <string_view>
#include <utility>
#include <vector>

constexpr std::array<std::array<int, 2>, 4> directions{{
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0},
}};

enum Direction {
  Right,
  Down,
  Left,
  Up,
};

constexpr Direction fromStr(std::string_view d) {
  if (d == "U") {
    return Up;
  }

  if (d == "D") {
    return Down;
  }

  if (d == "L") {
    return Left;
  }

  if (d == "R") {
    return Right;
  }

  // unreachable, at least for the problem constraints.
  std::unreachable();
}

constexpr std::array<int, 2> getDelta(std::string_view d) {
  return directions[fromStr(d)];
}

// The food appears one-by-one, and will never appear on a block occupied by
// the snake.
// Upon eating a food, the snake length and score increases by 1.
// Lose if the snake goes out of bounds, or collides with its body.
//
// Hm. How to track body? Clearly, using a 2D matrix to track positions will be
// unfeasible, in terms of implementation.
// Hm. Seems like using a deque would be feasible. Upon moving, if no food is
// eating, pop the earliest pushed position.
// Push the new position.
// Also need a HashSet, or a presence array to check for the snake's body.
class SnakeGame {
 public:
  SnakeGame(int width, int height, std::vector<std::vector<int>>& food)
      : width(width),
        height(height),
        snake(height, std::vector<bool>(width, false)),
        fIt(food.begin()),
        fEnd(food.end()) {
    pos.emplace_back(0, 0);
    snake[0][0] = true;
  }

  int move(std::string_view direction) {
    auto [r, c] = pos.back();
    auto [dr, dc] = getDelta(direction);

    int nr = r + dr;
    int nc = c + dc;

    // check out of bounds.
    // NOTE:
    // It is NOT okay to do tail-collision check here.
    // Need to determine whether the Snake's tail shortens, first.
    if (nr < 0 || nr >= height || nc < 0 || nc >= width) {
      return -1;
    }

    bool willEat = false;
    if (fIt != fEnd) {
      int foodR = (*fIt)[0];
      int foodC = (*fIt)[1];

      if (nr == foodR && nc == foodC) {
        ++score;
        ++fIt;
        willEat = true;
      }
    }

    if (!willEat && !pos.empty()) {
      auto [expireR, expireC] = pos.front();
      pos.pop_front();
      snake[expireR][expireC] = false;
    }

    // Check for body-collision
    if (snake[nr][nc]) {
      return -1;
    }
    snake[nr][nc] = 1;
    pos.emplace_back(nr, nc);
    return score;
  }

 private:
  int score{0};
  int width{-1};
  int height{-1};

  std::deque<std::pair<int, int>> pos;
  std::vector<std::vector<bool>> snake;

  std::vector<std::vector<int>>::iterator fIt;
  const std::vector<std::vector<int>>::iterator fEnd;
};

/**
 * Your SnakeGame object will be instantiated and called as such:
 * SnakeGame* obj = new SnakeGame(width, height, food);
 * int param_1 = obj->move(direction);
 */
