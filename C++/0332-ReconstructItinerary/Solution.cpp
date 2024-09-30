#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <cstdint>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class Solution {
private:
  void dfs(unordered_map<string_view, vector<string_view>> &adj,
           vector<string> &result, string_view curr) {
    vector<string_view> &neighbours = adj[curr];
    while (!neighbours.empty()) {
      string_view to = neighbours.back();
      neighbours.pop_back();
      dfs(adj, result, to);
    }
    // If its the last node and has no outgoing edges, then append to the result
    result.emplace_back(curr);
  }

public:
  vector<string> findItinerary(vector<vector<string>> &tickets) {
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
    unordered_map<string_view, vector<string_view>> adj;
    for (const auto &edge : tickets) {
      string_view from = edge[0];
      string_view to = edge[1];

      adj[from].push_back(to);
    }

    for (auto &[key, neighbours] : adj) {
      // Sort to traverse in Lexicographical order. However, sort in
      // descending order instead for efficient pop_back operations.
      sort(neighbours.rbegin(), neighbours.rend());
    }

    vector<string> result;
    dfs(adj, result, "JFK");

    // There is no need to check that the result vector is valid, i.e.,
    // result.size() == tickets.size() + 1; question guarantees a valid eulerian
    // path.
    reverse(result.begin(), result.end());

    return result;
  }
};
