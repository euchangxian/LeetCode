#include <functional>
#include <queue>
#include <vector>

class Solution {
 public:
  double maxProbability(int n,
                        std::vector<std::vector<int>>& edges,
                        std::vector<double>& succProb,
                        int start_node,
                        int end_node) {
    // Reduce to an SSSP problem.
    // For multiplication, to convert to a sum, intuition should be logarithms
    // To find the maximum probability, negate the edge weights.
    std::vector<std::vector<std::pair<double, int>>> modifiedEdges(n);
    for (int i = 0; i < edges.size(); ++i) {
      int from = edges[i][0];
      int to = edges[i][1];

      double weight = succProb[i];

      modifiedEdges[from].emplace_back(weight, to);
      modifiedEdges[to].emplace_back(weight, from);
    }

    std::vector<double> distances(n, 0);
    distances[start_node] = 1.0;

    // max heap instead of usual min heap to pop the greatest probability first
    std::priority_queue<std::pair<double, int>,
                        std::vector<std::pair<double, int>>,
                        std::less<std::pair<double, int>>>
        pq;
    pq.emplace(1.0, start_node);

    while (!pq.empty()) {
      auto [currProb, currNode] = pq.top();
      pq.pop();

      for (const auto& [prob, to] : modifiedEdges[currNode]) {
        if (distances[to] < currProb * prob) {
          distances[to] = currProb * prob;
          pq.emplace(distances[to], to);
        }
      }
    }
    return distances[end_node];
  }
};
