#include <vector>

class Solution {
 public:
  bool canReach(std::vector<int>& arr, int start) {
    // non-negative integers arr.
    // Start at start index. At index i, can jump to i+arr[i], or i-arr[i].
    // Return true if any index with value 0 can be reached.
    //
    // DFS/BFS?
    const auto n = static_cast<int>(arr.size());
    auto dfs = [&](this auto&& dfs, auto idx) {
      constexpr auto VISITED = -1;
      if (arr[idx] == VISITED) {
        return false;
      }
      if (arr[idx] == 0) {
        return true;
      }

      const auto jump = std::exchange(arr[idx], VISITED);
      auto result = false;
      if (auto next = idx + jump; next < n) {
        result |= dfs(next);
      }

      if (auto next = idx - jump; next >= 0) {
        result |= dfs(next);
      }
      return result;
    };
    return dfs(start);
  }
};
