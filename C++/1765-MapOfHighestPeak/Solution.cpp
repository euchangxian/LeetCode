#include <array>
#include <cstddef>
#include <cstdlib>
#include <utility>
#include <vector>

constexpr std::array<std::array<int, 2>, 4> directions{{
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0},
}};

template <typename T, std::size_t Capacity>
class CircularQueue {
 public:
  void push(const T& value) {
    queue_[back_] = value;
    back_ = (back_ + 1) % Capacity;
  }

  template <typename... Args>
  void emplace(Args&&... args) {
    queue_[back_] = T(std::forward<Args>(args)...);
    back_ = (back_ + 1) % Capacity;
  }

  T& front() { return queue_[front_]; }

  const T& front() const { return queue_[front_]; }

  void pop() { front_ = (front_ + 1) % Capacity; }

  [[nodiscard]] bool empty() const noexcept { return front_ == back_; }

  std::size_t size() const noexcept {
    return (static_cast<int>(back_) - static_cast<int>(front_) + Capacity) %
           Capacity;
  }

 private:
  std::size_t front_{};
  std::size_t back_{};

  std::array<T, Capacity> queue_;
};

class Solution {
 public:
  std::vector<std::vector<int>> highestPeak(
      std::vector<std::vector<int>>& isWater) {
    // isWater[i][j] == 0 | 1
    // 0 => land, 1 => water.
    // Assign each cell a non-negative height such that
    // - each water cell is of height 0
    // - Any two adjacent cells must have an absolute height diff of at most 1.
    // Find the maximum possible height that has a valid assignment.
    //
    // Note that without accounting for the max, simply assigning land cells
    // 1 will be valid.
    // However, since we want to maximise, while maintaining a maximum diff of
    // 1 for each adjacent cells, seems like a shortest path problem,
    // BFS from each water cell, relaxing the shortest distance to each land
    // cell.
    // Is this the most optimal though?
    const int m = isWater.size();
    const int n = isWater[0].size();

    CircularQueue<std::pair<int, int>, 800'000> frontier;
    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        if (isWater[r][c]) {
          isWater[r][c] = 0;
          frontier.emplace(r, c);
        } else {
          isWater[r][c] = -1;
        }
      }
    }

    while (!frontier.empty()) {
      int sz = frontier.size();
      while (sz--) {
        const auto [r, c] = frontier.front();
        frontier.pop();

        for (const auto [dr, dc] : directions) {
          const int nr = r + dr;
          const int nc = c + dc;

          if (nr < 0 || nc < 0 || nr >= m || nc >= n || isWater[nr][nc] != -1) {
            continue;
          }
          isWater[nr][nc] = isWater[r][c] + 1;
          frontier.emplace(nr, nc);
        }
      }
    }
    return isWater;
  }
};
