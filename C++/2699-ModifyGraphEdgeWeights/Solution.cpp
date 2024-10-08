#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

int const INF = 2e9;
using namespace std;
class Solution {
 private:
  int dijkstra(int n,
               vector<vector<pair<int, int>>> const& adj,
               int src,
               int dest) {
    // Distance estimates to each node from source
    vector<int> distance(n, INF);
    distance[src] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        frontier;

    frontier.emplace(0, src);
    while (!frontier.empty()) {
      auto [currDist, currNode] = frontier.top();
      frontier.pop();

      if (currNode == dest) {
        break;  // To reconstruct path
      }

      for (auto const& [weight, next] : adj[currNode]) {
        if (currDist + weight < distance[next]) {
          // Relax estimates
          distance[next] = currDist + weight;
          frontier.emplace(distance[next], next);
        }
      }
    }

    return distance[dest];
  }

 public:
  vector<vector<int>> modifiedGraphEdges(int n,
                                         vector<vector<int>>& edges,
                                         int source,
                                         int destination,
                                         int target) {
    // N nodes from 0 to n-1.
    // edges[i] = [ai, bi, wi] => undirected edge between ai and bi with weight
    // wi
    // weights are either -1 or > 0.
    // Modify all -1 weights to values in the range [1, 2 * 10e9] such that
    // SSSP between source and destination node is equal to target
    //
    // Dijkstra's won't work out of the box due to negative and positive weights
    // Minimum weight is 1.
    // Therefore, edges with weight = -1 can be mapped to weight of 1 first.
    // If a shortest path is found with total weight <= target means its viable?
    // Refining a little, the number of such -1 edges need to be maintained.
    // Let this count be k.
    // If weight + (k * 1) <= target AND weight + (k * 2 * 10e9) >= target,
    // then the path is viable.
    // However, since target <= 10e9, as long as there is one such edge, then
    // the second condition always fulfilled.

    vector<vector<pair<int, int>>> graph(n);

    for (auto const& edge : edges) {
      if (edge[2] == -1) {
        continue;  // skip modifiable edges
      }

      int node1 = edge[0];
      int node2 = edge[1];
      int weight = edge[2];
      graph[node1].emplace_back(weight, node2);
      graph[node2].emplace_back(weight, node1);
    }

    // Run dijkstra on the graph without the modifiable edges.
    int shortestDistance = dijkstra(n, graph, source, destination);

    // If the shortest path is already less than the target, then adding
    // any modifiable edges will not decrease the shortest path to reach the
    // target
    if (shortestDistance < target) {
      return {};
    }

    bool alreadyMatchedTarget = shortestDistance == target;
    for (auto& edge : edges) {
      if (edge[2] > 0) {
        continue;  // Skip unmodifiable weights.
      }

      // This modifiable edge is not relevant to our shortest path
      if (alreadyMatchedTarget) {
        edge[2] = INF;
        continue;
      }

      // Otherwise, try relaxing the edge by setting it to the minimum
      // weight possible (1 to 2e9)
      edge[2] = 1;
      int node1 = edge[0];
      int node2 = edge[1];
      graph[node1].emplace_back(1, node2);
      graph[node2].emplace_back(1, node1);

      int relaxedPath = dijkstra(n, graph, source, destination);
      if (relaxedPath <= target) {
        // If relaxing the edge allows us to find a shorter path that is within
        // the target then simply set this edge weight to the difference.
        // LTE check here, since any path without modifiable edges, and is
        // less than target would have already been rejected earlier
        edge[2] = target - relaxedPath + 1;
        alreadyMatchedTarget = true;
      }
    }

    if (!alreadyMatchedTarget) {
      return {};
    }
    return edges;
  }
};
