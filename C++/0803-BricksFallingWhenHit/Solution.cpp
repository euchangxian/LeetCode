#include <cstddef>
#include <cstdlib>
#include <iterator>
#include <ranges>
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
  std::vector<int> hitBricks(std::vector<std::vector<int>>& grid,
                             std::vector<std::vector<int>>& hits) {
    // Given binary grid[i][j], where 0 indicates empty, 1 indicates brick.
    //
    // A brick is stable if:
    // - Connected to top of the grid, or
    // - any adjacent brick is stable.
    //
    // Given hits, where hits[i] = [r, c] means to remove ANY brick at (r, c).
    // If any brick is no longer stable, then erase it.
    //
    // Return result[i] indicating the number of bricks that will fall after
    // the ith erasure.
    //
    // Naively, simulate each brick removal by:
    // iterating through and Unioning bricks, removing unstable bricks after.
    //
    // BUT, we can do better by adjusting our perspective.
    // Union Find has one limitation in that it is not reversible, i.e., not
    // associative. After union-ing bricks, we are unable to reverse the
    // union to simulate the removal of a brick.
    //
    // Thus, what if we were to do it in reverse? First, remove all bricks
    // indicated by the hits array.
    // Then, iteratively add the remove-d bricks and count.
    //
    // IMPLEMENTATION-details: First union all bricks with a sentinel STABLE,
    // if it is connected to the top. Then iterate and connect all other bricks.
    const int m = grid.size();
    const int n = grid[0].size();
    const int STABLE = m * n;

    // need to handle hits that did not have a brick, to avoid adding a brick
    // that never exist later on.
    // Thus, blanket -= 1, where -1 will indicate originally empty, 0 indicates
    // had a brick.
    for (const auto& hit : hits) {
      --grid[hit[0]][hit[1]];
    }

    UnionFind G(m * n + 1);

    // For the first iteration, we can't provide answer[n-1] yet, since we need
    // to know the change in the number of stable bricks from state[n-2] to
    // state[n-1].
    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        int curr = r * n + c;
        if (grid[r][c] == 1) {
          // if bricks are attached to the top.
          if (r == 0) {
            G.unite(STABLE, curr);
          }

          // check right and bottom.
          if (c + 1 < n && grid[r][c + 1] == 1) {
            G.unite(curr, curr + 1);
          }

          if (r + 1 < m && grid[r + 1][c] == 1) {
            G.unite(curr, curr + n);
          }
        }
      }
    }

    std::vector<int> answer(hits.size());
    auto it = answer.rbegin();
    // Note that the actual number of bricks returned by this size operation
    // would have an extra 1 sentinel brick. But since we are only interested
    // in the difference, it does not matter.
    int prev = G.size(STABLE);
    for (const auto& hit : hits | std::ranges::views::reverse) {
      int r = hit[0];
      int c = hit[1];
      if (++grid[r][c] == 1) {
        int curr = r * n + c;
        if (r == 0) {
          G.unite(STABLE, curr);
        }

        // unite with cardinal bricks.
        for (const auto [dr, dc] : directions) {
          int nr = r + dr;
          int nc = c + dc;

          if (nr < 0 || nc < 0 || nr >= m || nc >= n || grid[nr][nc] != 1) {
            continue;
          }
          G.unite(curr, nr * n + nc);
        }

        *it = std::max(
            0, G.size(STABLE) - prev - 1);  // the re-added brick does not count
      } else {
        *it = 0;  // no brick was removed.
      }

      ++it;
      prev = G.size(STABLE);
    }

    return answer;
  }
};
