#include <cstddef>
#include <cstdlib>
#include <utility>
#include <vector>

class Solution {
 public:
  std::vector<int> getRow(int rowIndex) {
    std::vector<int> dp{1};

    for (int r = 1; r <= rowIndex; ++r) {
      std::vector<int> temp(r + 1, 0);
      temp.front() = 1;
      temp.back() = 1;

      for (int i = 1; i < temp.size() - 1; ++i) {
        temp[i] = dp[i - 1] + dp[i];
      }

      dp = std::move(temp);
    }
    return dp;
  }
};
