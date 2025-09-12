#include <queue>
#include <vector>

using i64 = long long;
class Solution {
 public:
  std::vector<int> countSteppingNumbers(int low, int high) {
    // A stepping number is an integer such that all of its adjacent digits
    // have an absolute difference of exactly 1.
    // Return a sorted list of all stepping numbers in the inclusive range
    // [low..high]
    // 0 <= low,high <= 2E9
    //
    // Seems "recursive".
    // [0..9] are trivially stepping numbers, or rather: [0, 1], [2], ..., [9]
    // For each digit in the tenth-place, add -1 and +1 to get the stepping
    // number. e.g., [10, 12], [21, 23], ..., [87, 89], [98]
    // Then, for each digit in the hundreths-place, we still need the tenths
    // and ones to be stepping, so we append the lists of the corresponding
    // -1 and +1 digits. e.g., (0)1::[01],[21,23],
    // 1010
    // Isnt this just BFS. Lol.
    std::vector<int> result;
    if (low == 0) {
      result.emplace_back(0);
    }

    std::queue<i64> frontier;
    for (int i = 1; i <= 9; ++i) {
      frontier.emplace(i);
    }
    while (!frontier.empty()) {
      auto curr = frontier.front();
      frontier.pop();

      if (low <= curr && curr <= high) {
        result.emplace_back(curr);
      }

      if (curr * 10 <= high) {
        i64 lastDigit = curr % 10;
        if (lastDigit > 0) {
          frontier.emplace(curr * 10 + lastDigit - 1);
        }
        if (lastDigit < 9) {
          frontier.emplace(curr * 10 + lastDigit + 1);
        }
      }
    }

    return result;
  }
};
