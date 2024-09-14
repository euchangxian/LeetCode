#include <algorithm>
#include <array>
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
private:
  void dfs(vector<int> const &nums, int const &maxOR, int &count, int currOR,
           int const idx) {
    if (idx >= nums.size()) {
      count += (currOR == maxOR);
      return;
    }

    dfs(nums, maxOR, count, currOR | nums[idx], idx + 1);
    dfs(nums, maxOR, count, currOR, idx + 1);
  }

public:
  int countMaxOrSubsetsNaive(vector<int> const &nums) {
    int maxOR = reduce(nums.begin(), nums.end(), 0,
                       [&nums](int const &a, int const &b) { return a | b; });

    int count = 0;
    int curr;
    dfs(nums, maxOR, count, curr, 0);

    return count;
  }
};
