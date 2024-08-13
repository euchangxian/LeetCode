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
  void dfs(vector<int> const &candidates, int const &target,
           vector<vector<int>> &combinations, vector<int> &current, int idx) {
    if (target == 0) {
      // Since there are no '0's, just prune the tree
      combinations.push_back(current);
      return;
    }

    if (idx >= candidates.size()) {
      // Out of bounds. Pruned
      return;
    }

    if (target < 0) {
      // Can not ever sum to target. Pruned.
      return;
    }

    // Otherwise, try adding this element
    current.push_back(candidates[idx]);
    dfs(candidates, target - candidates[idx], combinations, current, idx + 1);
    current.pop_back();

    // To skip this element, we need to skip all other elements that are the
    // same as this element. Since the array is sorted, we can skip adjacent
    // elements if they are equal
    while (idx + 1 < candidates.size() &&
           candidates[idx + 1] == candidates[idx]) {
      ++idx;
    }
    dfs(candidates, target, combinations, current, idx + 1);
  }

public:
  vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
    // To ensure that there are no duplicate combinations, we need to be able to
    // skip numbers that are already in the current combination
    sort(candidates.begin(), candidates.end());

    vector<vector<int>> combinations;
    vector<int> current;
    dfs(candidates, target, combinations, current, 0);

    return combinations;
  }
};