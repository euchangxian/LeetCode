#include <algorithm>
#include <vector>

class Solution {
 public:
  std::vector<int> missingRolls(std::vector<int>& rolls, int mean, int n) {
    int m = rolls.size();
    int expectedSum = (n + m) * mean;
    for (int num : rolls) {
      expectedSum -= num;
    }

    if (expectedSum > n * 6 || expectedSum < n * 1) {
      return {};
    }

    std::vector<int> result(n, 0);

    // Pigeonhole principle
    // Place at least this many pigeons into each hole first
    // Remainder can be distributed to the holes
    int pigeonRoll = expectedSum / n;
    expectedSum -= n * pigeonRoll;

    for (int i = 0; i < n; ++i) {
      int additionalPigeons = 0;
      if (expectedSum) {
        additionalPigeons = std::min(6 - pigeonRoll, expectedSum);
        expectedSum -= additionalPigeons;
      }
      result[i] = pigeonRoll + additionalPigeons;
    }

    return result;
  }
};
