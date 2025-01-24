#include <cstddef>
#include <cstdlib>
#include <queue>
#include <vector>

class Solution {
 public:
  std::vector<int> eventualSafeNodes(std::vector<std::vector<int>>& graph) {
    // UF. Build the graph, then find terminal nodes.
    // Hm. Not so straightforward. Only want Nodes whose edges lead to another
    // Safe Node, or a Terminal Node.
    // Feels like topological sort instead.
    // i.e., we want to process Terminal Nodes first.
    // Then, for nodes +1 away, if all its path lead to a Terminal Node,
    // then it is a Safe Node (can be marked as Terminal too).
    //
    // Issue is the direction of edges. Instead of indegree = 0, we want
    // outdegree = 0.
    // Could preprocess and reverse edges.
    // Though semantics change a little.
    // Seems like if the frontier explored are all Terminal/Safe, then the
    // next frontier should be all Terminal/Safe too?
    // Therefore, the only case where nodes are not Terminal/Safe, are when
    // it has cycles.
    // Hm. With this, can we avoid reversing the graph and just find cycles.
    // Nope, look at TC1.
    const std::size_t n = graph.size();

    std::queue<int> frontier;
    std::vector<bool> safe(n, false);
    std::vector<int> indegree(n);
    std::vector<std::vector<int>> adj(n);
    for (int u = 0; u < n; ++u) {
      for (int v : graph[u]) {
        adj[v].push_back(u);  // reverse.
      }

      // since we are reversing outgoing edges, we can determine the
      // corresponding indegree.
      indegree[u] = graph[u].size();
      if (indegree[u] == 0) {
        frontier.push(u);
        safe[u] = true;
      }
    }

    while (!frontier.empty()) {
      int curr = frontier.front();
      frontier.pop();

      for (int next : adj[curr]) {
        if (--indegree[next] == 0) {
          frontier.push(next);
          safe[next] = true;
        }
      }
    }

    std::vector<int> result;
    result.reserve(n);
    for (int v = 0; v < n; ++v) {
      if (safe[v]) {
        result.push_back(v);
      }
    }
    return result;
  }
};
