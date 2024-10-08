#include <stack>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using std::string, std::string_view, std::vector, std::pair, std::unordered_map,
    std::unordered_set;
class Solution {
 private:
  double dfs(const unordered_map<string_view,
                                 vector<pair<string_view, double>>>& graph,
             const string_view from,
             const string_view to) {
    if (graph.find(from) == graph.end() || graph.find(to) == graph.end()) {
      return -1.0;
    }

    unordered_set<string_view> seen;

    // {node, resultSoFar}
    std::stack<pair<string_view, double>> stack;
    stack.emplace(from, 1.0);
    seen.insert(from);
    while (!stack.empty()) {
      const auto [curr, answer] = stack.top();
      stack.pop();
      seen.insert(curr);

      if (curr == to) {
        // Early return
        return answer;
      }

      if (graph.find(curr) == graph.end()) {
        continue;
      }

      for (const auto& [neighbour, weight] : graph.at(curr)) {
        if (!seen.count(neighbour)) {
          stack.emplace(neighbour, answer * weight);
        }
      }
    }
    // If no path to the destination is found, then return -1.0
    return -1.0;
  }

 public:
  vector<double> calcEquation(vector<vector<string>>& equations,
                              vector<double>& values,
                              vector<vector<string>>& queries) {
    // can be modelled as a Graph question.
    // Nodes will be the variables.
    // Edges are weighted, directed edges, whose weights are given by the
    // vector values.
    //
    // E.g., given equation [a, b] which represents a divided by b, and the
    // result of which is given by values[j], we can connect an edge from a to
    // b with the weight values[j]. Similarly, we can connect an edge from b
    // back to a with a weight 1/values[j].
    //
    // Therefore, suppose we have built our Graph, given a query [c, d], we
    // can start a DFS from the node c, a initial seed of 1.0 and find a path
    // to d, multiplying the weights of the edges along the way.

    // {from : {to, weight}}
    unordered_map<string_view, vector<pair<string_view, double>>> graph;

    // Given valid inputs, there isnt a need to check that the size of the
    // equations and values are equal
    for (size_t i = 0; i < equations.size(); ++i) {
      const string_view numerator = equations[i][0];
      const string_view denominator = equations[i][1];

      graph[numerator].emplace_back(denominator, values[i]);
      graph[denominator].emplace_back(numerator, 1 / values[i]);
    }

    vector<double> answers;
    answers.reserve(queries.size());
    for (const auto& query : queries) {
      const string_view from = query[0];
      const string_view to = query[1];

      answers.push_back(dfs(graph, from, to));
    }
    return answers;
  }
};
