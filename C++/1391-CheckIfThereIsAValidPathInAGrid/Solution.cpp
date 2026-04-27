#include <array>
#include <utility>
#include <vector>

enum Street {
  LeftRight = 1,
  UpDown = 2,
  LeftDown = 3,
  DownRight = 4,
  LeftUp = 5,
  UpRight = 6,
};

enum Dir {
  Right = 0,
  Down = 1,
  Left = 2,
  Up = 3,
  Invalid = 4,
};

constexpr std::array<std::array<int, 2>, 4> directions{{
    {0, 1},   // right
    {1, 0},   // down
    {0, -1},  // left
    {-1, 0},  // up
}};

// transitions[road][dir] = dir
constexpr auto transitions = std::array{
    std::array{
        Dir::Invalid,
        Dir::Invalid,
        Dir::Invalid,
        Dir::Invalid,
    },  // placeholder
    std::array{
        Dir::Right,
        Dir::Invalid,
        Dir::Left,
        Dir::Invalid,
    },  // left-right
    std::array{
        Dir::Invalid,
        Dir::Down,
        Dir::Invalid,
        Dir::Up,
    },  // up-down
    std::array{
        Dir::Down,
        Dir::Invalid,
        Dir::Invalid,
        Dir::Left,
    },  // left-down
    std::array{
        Dir::Invalid,
        Dir::Invalid,
        Dir::Down,
        Dir::Right,
    },  // down-right
    std::array{
        Dir::Up,
        Dir::Left,
        Dir::Invalid,
        Dir::Invalid,
    },  // left-up
    std::array{
        Dir::Invalid,
        Dir::Right,
        Dir::Up,
        Dir::Invalid,
    },  // up-right
};

constexpr auto startDirs = std::array{
    std::pair{Dir::Invalid, Dir::Invalid},  // placeholder
    std::pair{Dir::Invalid, Dir::Right},    // left-right
    std::pair{Dir::Invalid, Dir::Down},     // up-down
    std::pair{Dir::Invalid, Dir::Down},     // left-down
    std::pair{Dir::Down, Dir::Right},       // down-right
    std::pair{Dir::Invalid, Dir::Invalid},  // left-up
    std::pair{Dir::Invalid, Dir::Right},    // up-right
};

class Solution {
 public:
  bool hasValidPath(std::vector<std::vector<int>>& grid) {
    // Determine if there is a valid path the starts from top-left, ends
    // at bottom-right.
    //
    // Note that the cells need to be combined in compatible ways.
    // To go in the right-direction from cell i to cell j,
    // cell i must be one of: LeftRight, UpRight, DownRight,
    // whereas cell j must be one of: LeftRight, LeftDown, LeftUp
    // i..e, the direction of movement must be considered alongside
    // the types of cell i and cell j.
    // Once we resolve this canMove, the problem becomes a trivial BFS/DFS.
    //
    // May not even need to resolve. Just follow the path since there are no
    // forks except for the first piece.
    const auto m = static_cast<int>(grid.size());
    const auto n = static_cast<int>(grid[0].size());
    if (m == 1 && n == 1) {
      return true;
    }

    auto dfs = [&](auto dir) {
      if (dir == Dir::Invalid) {
        return false;
      }

      // we do not need to store an entire visited set. If the grid has a cycle,
      // then it MUST revisit the starting point.
      auto [r, c] = directions[dir];
      while (r >= 0 && r < m && c >= 0 && c < n) {
        dir = transitions[grid[r][c]][dir];
        if (dir == Dir::Invalid) {
          return false;
        }

        // cycle
        if (r == 0 && c == 0) {
          return false;
        }

        // destination
        if (r == m - 1 && c == n - 1) {
          return true;
        }

        auto [dr, dc] = directions[dir];
        r += dr;
        c += dc;
      }

      return false;
    };

    auto [d1, d2] = startDirs[grid[0][0]];
    return dfs(d1) || dfs(d2);
  }
};
