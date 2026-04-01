#include <algorithm>
#include <stack>
#include <string_view>
#include <vector>

class Solution {
 public:
  std::vector<int> survivedRobotsHealths(std::vector<int>& positions,
                                         std::vector<int>& healths,
                                         std::string_view directions) {
    const auto n = static_cast<int>(positions.size());
    std::vector<int> robots = std::vector<int>(n);
    for (int i = 0; i < n; ++i) {
      robots[i] = i;
    }

    std::sort(robots.begin(), robots.end(), [&positions](int i, int j) {
      // Ensure 1-indexed Robots is converted to 0-indexed positions
      return positions[i] < positions[j];  // process leftmost to rightmost
    });

    std::vector<int> result;
    // Stores robots going to the right only (monotonic).
    std::stack<int> goingRight;
    for (auto curr : robots) {
      if (directions[curr] == 'R') {
        goingRight.push(curr);
        continue;
      }

      while (!goingRight.empty()) {
        auto top = goingRight.top();
        if (healths[top] == healths[curr]) {
          healths[top] = 0;
          healths[curr] = 0;
          goingRight.pop();
          break;
        } else if (healths[top] > healths[curr]) {
          --healths[top];
          healths[curr] = 0;
          break;
        } else {
          --healths[curr];
          healths[top] = 0;
          goingRight.pop();
        }
      }
    }

    for (auto health : healths) {
      if (health > 0) {
        result.push_back(health);
      }
    }

    return result;
  }
};
