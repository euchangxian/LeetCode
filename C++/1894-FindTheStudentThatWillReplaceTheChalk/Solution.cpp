#include <functional>
#include <numeric>
#include <vector>

class Solution {
 public:
  int chalkReplacer(std::vector<int>& chalk, int k) {
    long long sum = std::reduce(chalk.begin(), chalk.end(), 0LL, std::plus<>{});

    // remaining
    k = (k % sum);
    for (int i = 0; i < chalk.size(); ++i) {
      k -= chalk[i];
      if (k < 0) {
        return i;
      }
    }
    return -1;  // Should not reach this point
  }
};
