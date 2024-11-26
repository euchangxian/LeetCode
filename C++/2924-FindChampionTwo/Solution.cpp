#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  int findChampion(int n, std::vector<std::vector<int>>& edges) {
    // n teams numbered from 0 to n-1.
    // Each team is also a node in a Directed Acyclic Graph.
    //
    // Given 2D edges of length m, edge[i] = [u, v] indicating a directed edge
    // from node u to node v.
    // A directed edge from u to v means that team a is stronger than team b.
    //
    // Return the team that will be the champion if there is a unique champion.
    // Otherwise return -1.
    //
    // Seems like topological sort. More specficially, Kahn's which uses BFS.
    // But doesnt this just require counting the indegree of nodes? If a node
    // has 0 indegree, return that node. If there are more than one node with
    // 0 indegree, return -1.
    std::vector<int> indegree(n, 0);
    for (const auto& edge : edges) {
      ++indegree[edge[1]];
    }

    int champion = -1;
    for (int i = 0; i < n; ++i) {
      if (indegree[i] == 0) {
        // check if there is already an earlier node that had indegree = 0.
        if (champion != -1) {
          return -1;
        }
        champion = i;
      }
    }

    return champion;
  }
};
