#include <array>
#include <vector>

constexpr std::size_t MAX_PID = 5E4;
class Solution {
 public:
  std::vector<int> killProcess(std::vector<int>& pid,
                               std::vector<int>& ppid,
                               int kill) {
    // n processes forming a rooted tree structure.
    // - pid[i] is the ID of the ith process
    // - ppid[i] is the ID of the parent of the ith process.
    // Kill id, and all its children.
    // Return in any order the list of processes killed.
    //
    // UnionFind, do not connect the kill node to its parents.
    const auto n = static_cast<int>(pid.size());

    std::array<int, MAX_PID + 1> indexOf{};
    for (int i = 0; i < n; ++i) {
      indexOf[pid[i]] = i;
    }

    std::vector<std::vector<int>> adj(n);
    for (int i = 0; i < n; ++i) {
      if (ppid[i] == 0) {
        continue;
      }
      adj[indexOf[ppid[i]]].emplace_back(indexOf[pid[i]]);
    }

    std::vector<int> result;
    auto dfs = [&](this auto&& dfs, int curr) -> void {
      result.emplace_back(pid[curr]);
      for (auto next : adj[curr]) {
        dfs(next);
      }
    };
    dfs(indexOf[kill]);
    return result;
  }
};
