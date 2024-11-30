#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <unordered_map>
#include <utility>
#include <vector>

class Solution {
 private:
  void hierholzer(std::unordered_map<int, std::deque<int>>& adjList,
                  std::vector<std::vector<int>>& result,
                  int node) {
    auto& edges = adjList[node];
    while (!edges.empty()) {
      int next = edges.back();
      edges.pop_back();
      hierholzer(adjList, result, next);
      result.push_back({node, next});
    }
  }

 public:
  std::vector<std::vector<int>> validArrangement(
      std::vector<std::vector<int>>& pairs) {
    // An arrangement of pairs is valid if for every index i in [0..n-1],
    // end_i-1 == start_i.
    // i.e., the end of the (i-1)th pair is equal to the start of the ith pair.
    //
    // Naively, we would want to iterate through and for each pair of Pairs,
    // check if the start is equal to the end of the other.
    // With this, we can model this as a Graph problem, where Pairs are Nodes,
    // and two Pairs are connected to each other by an edge iff end_u ==
    // start_v.
    // Then, given a valid input, we can simply DFS the order.
    // O(n^2) bounded by the all-pairs check. Can we do better?
    // Sort by ascending order of start? Doesnt seem productive. There is no
    // guarantee that start_i < end_i. Just that start_i != end_i.
    // Maybe we can try to optimize the pairs-checking.
    // HashMap? Store start and end hashmaps. For each pair, if the end is found
    // in the start map, or vice-versa, then they are connected by an edge.
    // Does not really improve our runtime. This is because we need to use a
    // multi-map, and connecting the pairs will take O(n) time.
    //
    // Tapped-out.
    // Modelling this problem as a Graph problem is indeed correct. Just that
    // each for each pairs[i] = [u, v], the nodes are u, v and are connected by
    // an edge.
    //
    // Thus, we want to be able to find a path from u - ... -> z through some
    // set of intermediate nodes v1, v2, ... vk.
    // Since each Pair represents an Edge, and we want to use all the Edges,
    // we can reduce this to an Eulerian Path: A path that visits every Edge
    // exactly once.
    // For a Graph to contain an Eulerian Path,
    // - at most one vertex can have outdegree - indegree = 1 (start vertex)
    // - at most one vertex can have indegree - outdegree = 1 (end vertex)
    // - All other vertices must have equal in and out degrees.
    //
    // Of course, our problem is simplified greatly, given that the input
    // guarantees a valid Path.
    // Thus, we just need to find a Node with outdegree - indegree >= 1,
    // indicating that there are more outgoing edges than incoming edges.
    // Every other node is guaranteed to have at least indegree == outdegree,
    // with at most one node having indegree - outdegree = 1.
    std::unordered_map<int, int> outdegree;
    std::unordered_map<int, int> indegree;
    std::unordered_map<int, std::deque<int>> adjList;

    for (const auto& edge : pairs) {
      const int u = edge[0];
      const int v = edge[1];
      ++outdegree[u];
      ++indegree[v];

      adjList[u].push_back(v);
    }

    // find a starting node
    // default to first node, which given the valid inputs, will indicate
    // either an eulerian circuit, or the start of a eulerian path.
    int start = adjList.begin()->first;
    for (const auto& [node, _] : adjList) {
      if (outdegree[node] == indegree[node] + 1) {
        start = node;
        break;
      }
    }

    std::vector<std::vector<int>> result;
    result.reserve(pairs.size());

    hierholzer(adjList, result, start);

    std::reverse(result.begin(), result.end());
    return result;
  }
};
