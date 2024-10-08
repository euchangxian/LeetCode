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
  int chalkReplacer(vector<int>& chalk, int k) {
    long long sum = reduce(chalk.begin(), chalk.end(), 0LL, plus<>{});

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
