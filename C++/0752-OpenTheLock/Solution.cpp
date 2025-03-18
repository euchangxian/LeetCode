#include <array>
#include <bitset>
#include <cstddef>
#include <queue>
#include <string>
#include <vector>

class Solution {
 public:
  int openLock(std::vector<std::string>& deadends, std::string target) {
    // Lock with 4 wheels; wheels have 10 states from '0' to '9'.
    // Wheel can turn in two directions, making it circular. i.e., one step to
    // go from '9' to '0'.
    // Initial state is "0000".
    // Deadends are exactly what it means. Wheels cannot turn anymore.
    // BFS? What are our nodes and edges?
    // Nodes are the 10^4 states of the wheel from 0000 to 9999.
    // Edges are just adjacent digits, e.g., 0000 -> 0001.
    // Converting to integers would prolly be simpler. From 0 to 9999. Trim
    // leading zeros.
    const int goal = std::stoi(target);

    std::bitset<kMaxStates> visited{};
    for (std::string& deadend : deadends) {
      const int dead = std::stoi(deadend);
      if (dead == 0) {
        return -1;
      }
      visited.set(dead);
    }

    std::queue<int> frontier;

    // start from 0
    frontier.push(0);
    visited.set(0);
    int steps = 0;
    while (!frontier.empty()) {
      int size = frontier.size();
      while (size--) {
        int curr = frontier.front();
        frontier.pop();

        if (curr == goal) {
          return steps;
        }

        // Add adjacent states if not visited.
        // Each wheel can be turned in reverse or otherwise.
        // Therefore, there are 4 * 2 adjacent states (4 wheels, 2 directions).
        for (int neighbour : adjacentStates(curr)) {
          if (!visited.test(neighbour)) {
            frontier.push(neighbour);
            visited.set(neighbour);
          }
        }
      }
      ++steps;
    }

    return -1;
  }

 private:
  static constexpr int kMaxStates = 10000;

  std::array<int, 8> adjacentStates(int current) {
    std::array<int, 8> adjacent{};

    int multiplier = 1;  // up to 1000
    for (int i = 0; i < 4; ++i) {
      int digit = (current / multiplier) % 10;  // extract the LSB

      int up = (digit + 1) % 10;          // turn wheel up, i.e. + 1
      int down = (digit + -1 + 10) % 10;  // turn wheel down, i.e. - 1

      // Minus multiplier * digit to zero out the corresponding digit,
      // effectively replacing it.
      adjacent[i * 2] = current - (multiplier * digit) + (multiplier * up);
      adjacent[i * 2 + 1] =
          current - (multiplier * digit) + (multiplier * down);

      multiplier *= 10;
    }

    return adjacent;
  }
};
