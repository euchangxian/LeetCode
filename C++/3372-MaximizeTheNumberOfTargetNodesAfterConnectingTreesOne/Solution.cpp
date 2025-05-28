#include <algorithm>
#include <queue>
#include <utility>
#include <vector>

class Solution {
 public:
  std::vector<int> maxTargetNodes(std::vector<std::vector<int>>& edges1,
                                  std::vector<std::vector<int>>& edges2,
                                  int k) {
    // two trees with n and m nodes respectively.
    // Node u is target to node v if the number of edges on the path from u to
    // v is less than or equal to k.
    // Return answer, where
    // answer[i] is the maximum possible number of nodes target to node i of
    // tree1 by connecting tree1 and tree2 with an edge.
    //
    // Hm. We want to root tree2 in such a way that we maximise the number
    // of nodes closest to the root.
    // Then, the number of nodes can be obtained by greedily connecting the
    // root to node i
    // Hm. Root at arbitrary node, level-order? Hm. Not sufficient.
    // Naively, root at every node in tree2 and do a level-order traversal up to
    // depth k-1. This will give us the number of nodes to add.
    const int n = edges1.size() + 1;
    const int m = edges2.size() + 1;
    auto getAdj = [&](const auto& edges) {
      std::vector<std::vector<int>> adj(edges.size() + 1);
      for (const auto& edge : edges) {
        adj[edge[0]].push_back(edge[1]);
        adj[edge[1]].push_back(edge[0]);
      }
      return adj;
    };

    auto adj1 = getAdj(edges1);
    auto adj2 = getAdj(edges2);

    auto getMaxTarget = [&](const auto& adj, int root, int maxDist) {
      std::queue<std::pair<int, int>> frontier;
      int depth = 0;
      int count = 1;
      frontier.emplace(root, -1);
      while (!frontier.empty() && depth < maxDist) {
        int sz = frontier.size();
        while (sz--) {
          auto [curr, parent] = frontier.front();
          frontier.pop();

          for (int next : adj[curr]) {
            if (next == parent) {
              continue;
            }
            frontier.emplace(next, curr);
            ++count;
          }
        }
        ++depth;
      }
      return count;
    };

    int targets2 = 0;
    if (k > 0) {
      for (int i = 0; i < m; ++i) {
        targets2 = std::max(targets2, getMaxTarget(adj2, i, k - 1));
      }
    }

    std::vector<int> answer(n);
    for (int i = 0; i < n; ++i) {
      answer[i] = getMaxTarget(adj1, i, k) + targets2;
    }
    return answer;
  }
};
