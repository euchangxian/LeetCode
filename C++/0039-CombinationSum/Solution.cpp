#include <vector>

class Solution {
 private:
  void dfs(const std::vector<int>& candidates,
           std::vector<std::vector<int>>& combinations,
           std::vector<int>& current,
           int target,
           int idx) {
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
  std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates,
                                               int target) {
    std::vector<std::vector<int>> combinations;
    std::vector<int> current;

    dfs(candidates, combinations, current, target, 0);

    return combinations;
  }
};
