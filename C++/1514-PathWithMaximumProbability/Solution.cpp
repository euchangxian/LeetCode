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
  double maxProbability(int n, vector<vector<int>> &edges,
                        vector<double> &succProb, int start_node,
                        int end_node) {
    // Reduce to an SSSP problem.
    // For multiplication, to convert to a sum, intuition should be logarithms
    // To find the maximum probability, negate the edge weights.
    vector<vector<pair<int, double>>> modifiedEdges(n);
    for (int i = 0; i < edges.size(); ++i) {
      int from = edges[i][0];
      int to = edges[i][1];

      double weight = succProb[i];

      modifiedEdges[from].push_back({to, weight});
      modifiedEdges[to].push_back({from, weight});
    }

    vector<double> distances(n, 0);
    distances[start_node] = 1.0;

    priority_queue<pair<double, int>> pq;
    pq.push({1.0, start_node});

    while (!pq.empty()) {
      auto [currProb, currNode] = pq.top();
      pq.pop();

      for (auto const &[to, prob] : modifiedEdges[currNode]) {
        if (distances[to] < currProb * prob) {
          distances[to] = currProb * prob;
          pq.push({distances[to], to});
        }
      }
    }
    return distances[end_node];
  }
};

