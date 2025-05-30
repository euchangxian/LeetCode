#include <algorithm>
#include <limits>
#include <vector>

class Solution {
 public:
  int closestMeetingNode(std::vector<int>& edges, int node1, int node2) {
    // Given n nodes, each node has at most one outgoing edge.
    // edges[i]=u indicate a directed edge from node i to node u, or -1 if no
    // outgoing edge.
    // Return the index of the node that can be reached from BOTH node1 and
    // node2, such that the longest path from node1/node2 to the intermediate
    // node is minimised.
    // The graph can have cycles. But our answer should be bounded? Unless
    // the graph can be disconnected? Should be possible to be disconnected.
    //
    // Hm. Can start traversing starting from node1 then node2? The first
    // intersection is our answer.
    // There is a possible edge case with 1 -> x <-> 2, where the answer is
    // not node 2, but node x (if we start at node2, we will have found an
    // intersection, but that distance is 2, not optimal).
    const int n = edges.size();
    auto dfs = [&](this auto&& dfs, auto& distance, int curr) -> void {
      // no outgoing, and not already visited.
      if (int next = edges[curr]; next != -1 && distance[next] == -1) {
        distance[next] = distance[curr] + 1;
        dfs(distance, next);
      }
    };

    std::vector<int> dist1(n, -1), dist2(n, -1);
    dist1[node1] = dist2[node2] = 0;
    dfs(dist1, node1);
    dfs(dist2, node2);

    int result = -1;
    int minDist = std::numeric_limits<int>::max();
    for (int i = 0; i < n; ++i) {
      int d1 = dist1[i];
      int d2 = dist2[i];
      if (d1 != -1 && d2 != -1) {
        if (int longestDist = std::max(d1, d2); longestDist < minDist) {
          minDist = longestDist;
          result = i;
        }
      }
    }
    return result;
  }
};
