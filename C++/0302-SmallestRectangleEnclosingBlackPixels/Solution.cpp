#include <algorithm>
#include <array>
#include <utility>
#include <vector>

constexpr std::array<std::array<int, 2>, 4> directions{{
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0},
}};

enum Pixel : char { White = '0', Black = '1' };

class Solution {
 public:
  int minArea(std::vector<std::vector<char>>& image, int x, int y) {
    // m x n binary matrix image, 0 represents white, 1 represents black
    // Black pixels are connected.
    // Given (x, y), the location of 1 of the black pixel, return the area of
    // the smallest axis-aligned rectangle that encloses all black pixels.
    // Must be faster than O(mn) runtime complexity.
    //
    // Does axis-aligned mean parallel to x,y axes?
    // Anyways, the naive approach in O(mn) is simple: collect the minX,minY,
    // maxX,maxY coordinates.
    // Though, given that we must solve in faster-than O(mn), we must be able
    // to take advantage of the connected property.
    //
    // DFS. Lol. Collect the min,max (x, y) seen.
    std::pair<int, int> minmaxX{x, x};
    std::pair<int, int> minmaxY{y, y};
    dfs(image, minmaxX, minmaxY, x, y);

    auto [minX, maxX] = minmaxX;
    auto [minY, maxY] = minmaxY;
    return (maxX - minX + 1) * (maxY - minY + 1);
  }

 private:
  void dfs(std::vector<std::vector<char>>& image,
           std::pair<int, int>& minmaxX,
           std::pair<int, int>& minmaxY,
           int x,
           int y) {
    image[x][y] = Pixel::White;  // mark visited.
    for (const auto [dx, dy] : directions) {
      int nx = x + dx;
      int ny = y + dy;

      if (nx < 0 || ny < 0 || nx >= image.size() || ny >= image[0].size() ||
          image[nx][ny] != Pixel::Black) {
        continue;
      }

      auto& [minX, maxX] = minmaxX;
      minX = std::min(minX, nx);
      maxX = std::max(maxX, nx);

      auto& [minY, maxY] = minmaxY;
      minY = std::min(minY, ny);
      maxY = std::max(maxY, ny);
      dfs(image, minmaxX, minmaxY, nx, ny);
    }
  }
};
