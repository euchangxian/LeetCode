#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class Solution {
public:
  vector<vector<int>> spiralMatrixIII(int rows, int cols, int rStart,
                                      int cStart) {
    vector<vector<int>> visited;
    visited.reserve(rows * cols);
    visited.push_back({rStart, cStart});

    // Right, Down, Left, Up
    // Determined by iter
    vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    int iter = 0;
    while (true) {
      if (visited.size() == rows * cols) {
        break;
      }

      int stride = (iter / 2) + 1;
      auto const &[r, c] = directions[iter % 4];
      for (int i = 0; i < stride; ++i) {
        rStart += r;
        cStart += c;

        if (rStart >= 0 && rStart < rows && cStart >= 0 && cStart < cols) {
          visited.push_back({rStart, cStart});
        }
      }

      ++iter;
    }

    return visited;
  }
};
