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
  vector<int> missingRolls(vector<int> &rolls, int mean, int n) {
    int m = rolls.size();
    int expectedSum = (n + m) * mean;
    for (auto const &num : rolls) {
      expectedSum -= num;
    }

    if (expectedSum > n * 6 || expectedSum < n * 1) {
      return {};
    }

    vector<int> result(n, 0);

    // Pigeonhole principle
    // Place at least this many pigeons into each hole first
    // Remainder can be distributed to the holes
    int pigeonRoll = expectedSum / n;
    expectedSum -= n * pigeonRoll;

    for (int i = 0; i < n; ++i) {
      int additionalPigeons = 0;
      if (expectedSum) {
        additionalPigeons = min(6 - pigeonRoll, expectedSum);
        expectedSum -= additionalPigeons;
      }
      result[i] = pigeonRoll + additionalPigeons;
    }

    return result;
  }
};
