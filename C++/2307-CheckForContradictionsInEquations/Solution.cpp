#include <cstddef>
#include <cstdlib>
#include <stack>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using std::vector, std::string, std::string_view, std::pair, std::unordered_map,
    std::unordered_set, std::stack;
class Solution {
private:
  constexpr static double tolerance{10e-5};

  inline bool equal(const double ref, const double other) const noexcept {
    return std::abs(ref - other) < tolerance;
  }

  vector<double>
  dfs(const unordered_map<string_view, vector<pair<string_view, double>>>
          &graph,
      const string_view src, const string_view dest) {
    // no need to check that src and dest are in the graph.

    vector<double> answers;
    unordered_set<string_view> seen;

    stack<pair<string_view, double>> stk;
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
      for (const auto &[neighbour, weight] : graph.at(curr)) {
        if (!seen.count(neighbour)) {
          stk.emplace(neighbour, answer * weight);
        }
      }
    }
    return answers;
  }

public:
  bool checkContradictions(vector<vector<string>> &equations,
                           vector<double> &values) {
    // Similar to the EvaluateDivisions.
    // Nodes are Variables. Edges are weighted, directed edges whose weights
    // are given by the vector values.

    unordered_map<string_view, vector<pair<string_view, double>>> graph;
    for (size_t i = 0; i < equations.size(); ++i) {
      const string_view numerator = equations[i][0];
      const string_view denominator = equations[i][1];

      graph[numerator].emplace_back(denominator, values[i]);
      graph[denominator].emplace_back(numerator, 1 / values[i]);
    }

    // Once graph has been built, for each equation, find all alternate paths
    // to the destination. Verify that all are equal.
    // This is done by adding the result of a DFS-path into a vector instead
    // of returning early.
    for (size_t i = 0; i < equations.size(); ++i) {
      // The first element in this vector will always be the reference answer.
      // i.e. a direct edge from src to dest
      const string_view from = equations[i][0];
      const string_view to = equations[i][1];
      // Handle the case where from and to are the same, but the value is not 1
      if (from == to && !equal(values[i], 1.0)) {
        return true;
      }

      vector<double> answers = dfs(graph, from, to);

      const double ref = answers[0];
      for (size_t i = 1; i < answers.size(); ++i) {
        if (!equal(ref, answers[i])) {
          return true;
        }
      }
    }

    // No contradiction found
    return false;
  }
};
