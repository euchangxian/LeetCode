#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

class Solution {
 public:
  int minJumps(std::vector<int>& arr) {
    // Start at index 0.
    // In one step, jump from index i to index:
    // - i+1, i+1 < n
    // - i-1, i-1 >= 0
    // - j, arr[i] == arr[j], i!=j
    // Return the minimum number of steps to reach index n-1.
    //
    // Is this BFS/DFS, too?
    // Preprocess edges, i is connected to j if arr[i] == arr[j].
    //
    // First glance, doesn't seem like there's a need to jump backwards:
    // - but after an optimal teleport, jumping backwards may allow another
    //   optimal teleport
    const auto n = static_cast<int>(arr.size());
    if (n == 1) {
      return 0;
    }

    std::unordered_map<int, std::vector<int>> adj;
    for (int i = 0; i < n; ++i) {
      adj[arr[i]].push_back(i);
    }

    std::queue<int> frontier;
    std::vector<bool> visited(n, false);
    frontier.emplace(0);
    visited[0] = true;
    auto steps = 0;
    while (!frontier.empty()) {
      auto qLen = static_cast<int>(frontier.size());
      while (qLen--) {
        auto node = frontier.front();
        frontier.pop();

        if (node == n - 1) {
          return steps;
        }

        if (node - 1 >= 0 && !visited[node - 1]) {
          frontier.emplace(node - 1);
          visited[node - 1] = true;
        }
        if (node + 1 < n && !visited[node + 1]) {
          frontier.emplace(node + 1);
          visited[node + 1] = true;
        }

        for (auto next : adj[arr[node]]) {
          if (!visited[next]) {
            frontier.emplace(next);
            visited[next] = true;
          }
        }
        adj[arr[node]].clear();
      }
      ++steps;
    }
    std::unreachable();
  }
};
