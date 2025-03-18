#include <climits>
#include <queue>
#include <utility>
#include <vector>

class Solution {
 public:
  // BFS for minimum path, remove all edges in the minimum path, then
  // BFS again (until the new value is strictly larger)
  int secondMinimum(int n,
                    std::vector<std::vector<int>>& edges,
                    int time,
                    int change) {
    std::vector<std::vector<int>> adj(n);
    for (const auto& edge : edges) {
      int from = edge[0];
      int to = edge[1];

      // convert to 0-index
      adj[from - 1].push_back(to - 1);
      adj[to - 1].push_back(from - 1);  // bidirectional
    }

    // Store shortest distance/time to the node
    std::vector<int> dist1(n, INT_MAX);

    // Store second-shortest distance/ time to the node
    std::vector<int> dist2(n, INT_MAX);

    // {node, numberOfTimesSeen}
    std::queue<std::pair<int, int>> frontier;
    frontier.push({0, 1});
    dist1[0] = 0;
    while (!frontier.empty()) {
      auto [node, freq] = frontier.front();
      frontier.pop();

      // If the node is seen for the first time, then the
      // timeTaken is the shortest time to the node.
      int timeTaken = freq == 1 ? dist1[node] : dist2[node];

      // traffic signal is red at every odd number of `change` minutes
      // 2i * change + change
      if ((timeTaken / change) & 1) {
        // If red, then wait till the next time where it is green
        // can be difficult to understand, but its calculating the
        // next interval/time when the signal is green.
        timeTaken = ((timeTaken / change) + 1) * change;
      }
      // Add the time taken to traverse the edge
      timeTaken += time;

      for (int neighbour : adj[node]) {
        if (dist1[neighbour] == INT_MAX) {
          // First time seeing node, update shortest time
          dist1[neighbour] = timeTaken;
          frontier.push({neighbour, 1});
          continue;
        }

        // check that the current path is not traversed before, by comparing
        // dist1[neighbour] and timeTaken.
        if (dist2[neighbour] == INT_MAX && dist1[neighbour] != timeTaken) {
          // Check for early return
          if (neighbour + 1 == n) {
            return timeTaken;
          }

          dist2[neighbour] = timeTaken;
          frontier.push({neighbour, 2});
          continue;
        }
        // effectively ignores nodes that have been seen twice
      }
    }

    return 0;  // Only one node. 0 time taken
  }
};
