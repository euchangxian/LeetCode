#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <queue>
#include <vector>

class Solution {
 public:
  int longestCycle(std::vector<int>& edges) {
    // Observe that each node can only be part of a single cycle, given that it
    // only has at most one outgoing edge.
    // NOTE: This implies that visiting each node once is sufficient.
    //
    // Tried cyclic sorting and following the edges, but it is not guaranteed
    // that all the nodes on the path is on a cycle.
    //
    // Wow. Recall how Kahn's algorithm detects cycles.
    // By BFS-ing nodes with indegree = 0, eventually, all nodes will be
    // added and popped.
    // However, if there is a cycle, at the end of the algorithm, there will
    // still be nodes with indegree > 0.
    // Those nodes will therefore belong to a cycle, and we can walk the edges
    // to find the length of the cycles.

    const int n = edges.size();
    std::vector<int> indegree(n, 0);
    for (int i = 0; i < n; ++i) {
      if (edges[i] != -1) {
        ++indegree[edges[i]];
      }
    }

    std::queue<int> frontier;
    for (int i = 0; i < n; ++i) {
      if (indegree[i] == 0) {
        frontier.push(i);
      }
    }

    while (!frontier.empty()) {
      int node = frontier.front();
      frontier.pop();

      if (edges[node] != -1 && --indegree[edges[node]] == 0) {
        frontier.push(edges[node]);
      }
    }

    // At the end of Kahn's, check the cycle length of nodes with indegree > 0
    int longest = -1;
    for (int i = 0; i < n; ++i) {
      if (indegree[i] == 0) {
        continue;
      }

      int cycleLength = 1;
      int j = i;
      while (edges[j] != -1 && edges[j] != i) {
        // use as visited. Each node can only be part of a single cycle.
        --indegree[edges[j]];

        ++cycleLength;
        j = edges[j];
      }
      longest = std::max(longest, cycleLength);
    }

    return longest;
  }
};
