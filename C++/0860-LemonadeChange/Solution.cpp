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
  bool lemonadeChange(vector<int> &bills) {
    // Customer pay in bills {5, 10, 20}.
    // Start with no bills.
    // Therefore, consider the number of ways to return change to the customer
    // receive 5 => no change
    // receive 10 => return 5
    // receive 20 => return {5, 5, 5}, {5, 10}
    // Since 20 dollar bills are of no use, we dont need to track it
    vector<int> remainingChange = {0, 0};

    bool allCorrect = true;
    for (int const &bill : bills) {
      if (bill == 5) {
        ++remainingChange[0];
        continue;
      }

      if (bill == 10) {
        allCorrect = allCorrect && remainingChange[0]--;
        ++remainingChange[1];
        continue;
      }

      if (remainingChange[0] && remainingChange[1]) {
        --remainingChange[0];
        --remainingChange[1];
        continue;
      }

      if (remainingChange[0] > 2) {
        remainingChange[0] -= 3;
        continue;
      }

      // Early return
      return false;
    }

    return allCorrect;
  }
};
