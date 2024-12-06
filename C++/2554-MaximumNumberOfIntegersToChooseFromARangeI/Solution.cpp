#include <bitset>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  int maxCount(std::vector<int>& banned, int n, int maxSum) {
    // Seems like Greedy?
    // Greedily pick the smallest non-banned integer until <= maxSum.
    // Can we prove the Greedy Choice?
    // i.e., Proof by Cut-and-Paste:
    // 1. Suppose there exist x* such that x* > x.
    // 2. If x* + sum <= maxSum, then we can replace x* with x to form a
    //    smaller sum <= maxSum.
    std::bitset<10000 + 1> isBanned{};
    for (int num : banned) {
      isBanned.set(num);
    }

    int chosen = 0;
    int sum = 0;
    for (int i = 1; i <= n; ++i) {
      if (isBanned.test(i)) {
        continue;
      }

      if (sum + i > maxSum) {
        break;
      }
      ++chosen;
      sum += i;
    }
    return chosen;
  }
};
