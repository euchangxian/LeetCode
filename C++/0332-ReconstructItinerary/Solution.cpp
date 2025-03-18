#include <algorithm>
#include <array>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

class Solution {
 public:
  std::vector<std::string> findItinerary(
      std::vector<std::vector<std::string>>& tickets) {
    // ticket[i] = [from, to]
    // Therefore, Cities can be modelled as Nodes, tickets can be modelled as
    // a Directed Edge
    // To reconstruct the route from JFK to the last city. Seems like a
    // topological sort.
    // BUT, there are Cycles...
    // Topological Sort do not work with Cycles.
    // Looking at the question again, requirements are to use all Tickets
    // exactly once. Sounds like an Euler's circuit. But there is no requirement
    // to start and end at the same Node. Thus its an Euler's Path.
    // Question guarantees there is a valid Euler's Path
    // A (simple) Graph contains an Euler's Path if there is an even number of
    // odd-degree nodes.
    //
    // How do we find the Euler's Path?
    // Seems like greedily
    std::unordered_map<std::string_view, std::vector<std::string_view>> adj;
    for (const auto& edge : tickets) {
      std::string_view from = edge[0];
      std::string_view to = edge[1];

      adj[from].push_back(to);
    }

    for (auto& [key, neighbours] : adj) {
      // Sort to traverse in Lexicographical order. However, sort in
      // descending order instead for efficient pop_back operations.
      std::sort(neighbours.rbegin(), neighbours.rend());
    }

    std::vector<std::string> result;
    dfs(adj, result, "JFK");

    // There is no need to check that the result std::vector is valid, i.e.,
    // result.size() == tickets.size() + 1; question guarantees a valid eulerian
    // path.
    std::reverse(result.begin(), result.end());

    return result;
  }

 private:
  void dfs(
      std::unordered_map<std::string_view, std::vector<std::string_view>>& adj,
      std::vector<std::string>& result,
      std::string_view curr) {
    std::vector<std::string_view>& neighbours = adj[curr];
    while (!neighbours.empty()) {
      std::string_view to = neighbours.back();
      neighbours.pop_back();
      dfs(adj, result, to);
    }
    // If its the last node and has no outgoing edges, then append to the result
    result.emplace_back(curr);
  }
};
