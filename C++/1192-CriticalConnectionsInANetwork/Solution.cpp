#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  std::vector<std::vector<int>> criticalConnections(
      int n,
      std::vector<std::vector<int>>& connections) {
    // Tarjan's Algorithm to find Bridges, a slight modification to the
    // criteria as compared to Articulation Points.
    std::vector<std::vector<int>> adj(n);
    for (const auto& edge : connections) {
      adj[edge[0]].push_back(edge[1]);
      adj[edge[1]].push_back(edge[0]);
    }

    std::vector<int> discoveryTime(n, -1), lowestReachableTime(n, -1);

    std::vector<std::vector<int>> bridges;
    bridges.reserve(connections.size());

    int time = 0;

    // Root the graph at node 0.
    for (int u = 0; u < n; ++u) {
      if (discoveryTime[u] == -1) {
        tarjans(adj, discoveryTime, lowestReachableTime, bridges, time, u);
      }
    }

    return bridges;
  }

 private:
  void tarjans(const std::vector<std::vector<int>>& adj,
               std::vector<int>& discoveryTime,
               std::vector<int>& lowestReachableTime,
               std::vector<std::vector<int>>& bridges,
               int& time,
               int node,
               int parent = -1) const {
    // Side-note: for finding bridges, there is no need to keep track of the
    // number of childrens for the special case where the current node is the
    // root of the DFS tree.
    // Only necessary for Articulation Points.
    discoveryTime[node] = time++;
    lowestReachableTime[node] = discoveryTime[node];

    for (int next : adj[node]) {
      if (next == parent) {
        continue;
      }

      if (discoveryTime[next] != -1) {
        // Neighbour is an ancestor/non-trivial cycle.
        lowestReachableTime[node] =
            std::min(lowestReachableTime[node], discoveryTime[next]);
        continue;
      }

      // otherwise, undiscovered child.
      tarjans(adj, discoveryTime, lowestReachableTime, bridges, time, next,
              node);

      // check if this node <--> next edge is a Bridge.
      if (lowestReachableTime[next] > discoveryTime[node]) {
        bridges.push_back({node, next});
      }

      lowestReachableTime[node] =
          std::min(lowestReachableTime[node], lowestReachableTime[next]);
    }
  }
};
