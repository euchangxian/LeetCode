#include <algorithm>
#include <vector>

class Solution {
 public:
  int countCoveredBuildings(int n, std::vector<std::vector<int>>& buildings) {
    // Given n representing an nxn city
    // buildings[i] = [x, y] representing a unique building at coordinates
    // (x, y)
    // A building is covered if there is at least one building in all four
    // directions: Left, Right, Above, Below.
    // Return the number of covered buildings.
    //
    // What is considered in the direction?? Same x/y-coordinates, but different
    // y/x coordinates?

    // 1-indexed
    // min/max building's x-coordinate at the given y-coordinate
    // min/maxRow[y] = min/max{x}
    std::vector<int> minRow(n + 1, n + 1);
    std::vector<int> maxRow(n + 1, 0);

    std::vector<int> minCol(n + 1, n + 1);
    std::vector<int> maxCol(n + 1, 0);

    for (const auto& coord : buildings) {
      auto x = coord[0];
      auto y = coord[1];

      minRow[y] = std::min(minRow[y], x);
      maxRow[y] = std::max(maxRow[y], x);

      minCol[x] = std::min(minCol[x], y);
      maxCol[x] = std::max(maxCol[x], y);
    }

    int result = 0;
    for (const auto& coord : buildings) {
      auto x = coord[0];
      auto y = coord[1];

      if (x > minRow[y] && x < maxRow[y] && y > minCol[x] && y < maxCol[x]) {
        ++result;
      }
    }
    return result;
  }
};
