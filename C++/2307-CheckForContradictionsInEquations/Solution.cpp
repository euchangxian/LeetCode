#include <cstddef>
#include <cstdlib>
#include <stack>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

constexpr static double tolerance{10e-5};

bool equal(const double ref, const double other) noexcept {
  return std::abs(ref - other) < tolerance;
}

class Solution {
 public:
  bool checkContradictions(std::vector<std::vector<std::string>>& equations,
                           std::vector<double>& values) {
    // Similar to the EvaluateDivisions.
    // Nodes are Variables. Edges are weighted, directed edges whose weights
    // are given by the std::vector values.

    std::unordered_map<std::string_view,
                       std::vector<std::pair<std::string_view, double>>>
        graph;
    for (std::size_t i = 0; i < equations.size(); ++i) {
      const std::string_view numerator = equations[i][0];
      const std::string_view denominator = equations[i][1];

      graph[numerator].emplace_back(denominator, values[i]);
      graph[denominator].emplace_back(numerator, 1 / values[i]);
    }

    // Once graph has been built, for each equation, find all alternate paths
    // to the destination. Verify that all are equal.
    // This is done by adding the result of a DFS-path into a std::vector
    // instead of returning early.
    for (std::size_t i = 0; i < equations.size(); ++i) {
      // The first element in this std::vector will always be the reference
      // answer. i.e. a direct edge from src to dest
      const std::string_view from = equations[i][0];
      const std::string_view to = equations[i][1];
      // Handle the case where from and to are the same, but the value is not 1
      if (from == to && !equal(values[i], 1.0)) {
        return true;
      }

      std::vector<double> answers = dfs(graph, from, to);

      const double ref = answers[0];
      for (std::size_t i = 1; i < answers.size(); ++i) {
        if (!equal(ref, answers[i])) {
          return true;
        }
      }
    }

    // No contradiction found
    return false;
  }

 private:
  std::vector<double> dfs(
      const std::unordered_map<
          std::string_view,
          std::vector<std::pair<std::string_view, double>>>& graph,
      const std::string_view src,
      const std::string_view dest) {
    // no need to check that src and dest are in the graph.

    std::vector<double> answers;
    std::unordered_set<std::string_view> seen;

    std::stack<std::pair<std::string_view, double>> stk;
    stk.emplace(src, 1.0);
    while (!stk.empty()) {
      const auto [curr, answer] = stk.top();
      stk.pop();

      if (curr == dest) {
        answers.push_back(answer);
        continue;
      }

      // ORDER is important. Avoid adding the destination node into the visited
      // set.
      seen.insert(curr);
      for (const auto& [neighbour, weight] : graph.at(curr)) {
        if (!seen.count(neighbour)) {
          stk.emplace(neighbour, answer * weight);
        }
      }
    }
    return answers;
  }
};
