#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class Solution {
public:
  int networkDelayTime(vector<vector<int>> &times, int n, int k) {
    // times[i] = (ui, vi, wi), representing a directed edge from node u to node
    // v with a weight of w
    // From source node k, get the minimum time to reach all other nodes
    //
    // Looks like Dijkstra is possible, where running Dijkstra will give us the
    // shortest path tree. Then the maximum value of this shortest path tree can
    // be retrieved to give the answer.
    // What about Bellman Ford? Bellman Ford iteratively relaxes all edges
    vector<vector<pair<int, int>>> graph(n);
    for (auto const &edge : times) {
      int from = edge[0] - 1; // nodes are 1-indexed
      int to = edge[1] - 1;
      int weight = edge[2];

      graph[from].emplace_back(weight, to);
    }

    vector<int> distance(n, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        minHeap;

    int src = k - 1; // 1-indexed
    distance[src] = 0;
    minHeap.emplace(0, src);

    while (!minHeap.empty()) {
      auto [dist, from] = minHeap.top();
      minHeap.pop();

      for (auto const &[weight, to] : graph[from]) {
        if (dist + weight < distance[to]) {
          distance[to] = dist + weight;
          minHeap.emplace(dist + weight, to);
        }
      }
    }

    int minTime = *max_element(distance.begin(), distance.end());
    if (minTime == INT_MAX) {
      return -1; // If there are unreachable nodes
    }
    return minTime;
  }
};
