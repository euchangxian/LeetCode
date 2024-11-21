#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 private:
  enum State {
    UNGUARDED = 0,
    GUARDED = 1,
    GUARD = 2,
    WALL = 3,
  };

  const std::array<std::array<int, 2>, 4> directions{{
      {0, 1},
      {1, 0},
      {0, -1},
      {-1, 0},
  }};

  void guardCardinal(std::vector<std::vector<int>>& grid, int r, int c) {
    // DFS from [r, c]
    for (auto [dr, dc] : directions) {
      int nr = r + dr;
      int nc = c + dc;

      while (nr >= 0 && nc >= 0 && nr < grid.size() && nc < grid[0].size() &&
             grid[nr][nc] != State::GUARD && grid[nr][nc] != State::WALL) {
        grid[nr][nc] = State::GUARDED;
        nr += dr;
        nc += dc;
      }
    }
  }

 public:
  int countUnguarded(int m,
                     int n,
                     std::vector<std::vector<int>>& guards,
                     std::vector<std::vector<int>>& walls) {
    // m * n grid.
    // guard[i]/walls[j] = [row, col]  => position of ith/jth guard/wall
    // Guard can see every cell in the 4 cardinal direction, unless obstructed
    // by a Wall or another Guard.
    // A cell is guarded if there is at least one Guard who can see it.
    // Return number of unoccupied cells that are not guarded.
    //
    // Seems like Union Find. If there is a Guard in the cardinal direction of
    // a cell, then Cell = Guarded.
    // Not trivial to determine that though.
    // E.g., consider the case below, where a Cell is not in the cardinal
    // direction of a Guard, but is beside a guarded cell. Naive UF would mean
    // that the Cell is also considered Guarded.
    // _ _ ...
    // G ...
    // ...
    // What about collecting the [r, c] of each Guard and Wall into their own
    // (Multi-)Sets.
    // When at a Cell, check its [r, c].
    // WLOG, trivially, if either its row or column matches a Guard and no
    // Walls, it is Guarded.
    // If it matches a Guard and a Wall, determine if the Wall obstructs the
    // Guard.
    // The problem is the multi-set nature, which would require the Guard/Wall
    // with the closest distance to the current Cell.
    std::vector<std::vector<int>> grid(m, std::vector<int>(n));

    for (auto& guard : guards) {
      int r = guard[0], c = guard[1];
      grid[r][c] = State::GUARD;
    }

    for (auto& wall : walls) {
      int r = wall[0], c = wall[1];
      grid[r][c] = State::WALL;
    }

    for (auto& guard : guards) {
      int r = guard[0], c = guard[1];
      guardCardinal(grid, r, c);
    }

    auto isUnguarded = [](int state) -> bool {
      return state == State::UNGUARDED;
    };

    int unguarded = 0;
    for (auto& row : grid) {
      unguarded += std::count_if(row.begin(), row.end(), isUnguarded);
    }

    return unguarded;
  }
};
