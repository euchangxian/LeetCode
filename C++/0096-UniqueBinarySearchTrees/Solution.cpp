#include <cstddef>
#include <vector>

using namespace std;
class Solution {
 private:
  int solve(std::vector<int>& memo, int n) {
    if (n <= 1) {
      return 1;
    }

    if (memo[n]) {
      return memo[n];
    }

    for (int i = 1; i <= n; ++i) {
      memo[n] += solve(memo, i - 1) * solve(memo, n - i);
    }

    return memo[n];
  }

 public:
  int numTrees(int n) {
    std::vector<int> memo(n + 1, 0);
    return solve(memo, n);
  }
};
