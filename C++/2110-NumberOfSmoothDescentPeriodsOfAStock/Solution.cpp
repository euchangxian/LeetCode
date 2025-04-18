#include <vector>

using i64 = long long;
class Solution {
 public:
  i64 getDescentPeriods(std::vector<int>& prices) {
    i64 result = 1;
    int currSeq = 1;
    for (int i = 1; i < prices.size(); ++i) {
      if (prices[i] + 1 == prices[i - 1]) {
        ++currSeq;
      } else {
        currSeq = 1;
      }
      result += currSeq;
    }
    return result;
  }
};
