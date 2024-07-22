#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>

using namespace std;
class Solution {
public:
  vector<int> survivedRobotsHealths(vector<int> &positions,
                                    vector<int> &healths, string directions) {
    int n = positions.size();
    vector<int> robots = vector<int>(n);
    for (int i = 0; i < n; ++i) {
      robots[i] = i;
    }

    sort(robots.begin(), robots.end(), [&positions](int i, int j) {
      // Ensure 1-indexed Robots is converted to 0-indexed positions
      return positions[i] < positions[j]; // process leftmost to rightmost
    });

    vector<int> result;
    // Stores robots going to the right only (monotonic).
    stack<int> goingRight;
    for (int curr : robots) {
      if (directions[curr] == 'R') {
        goingRight.push(curr);
        continue;
      }

      while (!goingRight.empty()) {
        int top = goingRight.top();
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

    for (int health : healths) {
      if (health > 0) {
        result.push_back(health);
      }
    }

    return result;
  }
};

int main(int argc, char *argv[]) {
  vector<int> positions = {3, 5, 2, 6};
  vector<int> healths = {10, 10, 15, 12};
  string directions = "RLRL";

  Solution().survivedRobotsHealths(positions, healths, directions);
}
