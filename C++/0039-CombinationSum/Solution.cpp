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
private:
  void dfs(vector<int> const &candidates, vector<vector<int>> &combinations,
           vector<int> &current, int target, int idx) {
    if (target == 0) {
      combinations.push_back(current);
      return;
    }

    if (idx >= candidates.size()) {
      return;
    }

    if (target < 0) {
      return;
    }

    current.push_back(candidates[idx]);
    dfs(candidates, combinations, current, target - candidates[idx], idx);
    current.pop_back();
    dfs(candidates, combinations, current, target, idx + 1);

    return;
  }

public:
  vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
    vector<vector<int>> combinations;
    vector<int> current;

    dfs(candidates, combinations, current, target, 0);

    return combinations;
  }
};
