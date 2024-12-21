#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
  using i64 = long long;

 private:
  i64 postorder(std::vector<std::vector<int>>& adjList,
                std::vector<int>& values,
                int k,
                std::vector<bool>& visited,
                int node,
                int& result) {
    visited[node] = true;
    i64 componentSum = values[node];

    // recurse on child nodes.
    for (int neighbour : adjList[node]) {
      // Given that we mark a node as visited first, we are traversing through
      // parent-child edges.
      // Thus, if a node is already visited, it must be a parent.
      if (visited[neighbour]) {
        continue;
      }

      // recurse on child subtrees. If its component sum is already a multiple,
      // then exclude it from the current component sum.
      i64 childSum = postorder(adjList, values, k, visited, neighbour, result);
      if (childSum % k == 0) {
        ++result;  // split
      } else {
        componentSum += childSum;
      }
    }

    return componentSum;
  }

 public:
  int maxKDivisibleComponents(int n,
                              std::vector<std::vector<int>>& edges,
                              std::vector<int>& values,
                              int k) {
    // undirected tree, n nodes labelled 0 to n-1.
    // Given edges[i] = [a, b] indicating edge between nodes a and b, and
    // values[i] indicating the value of the ith node.
    // A split is valid if the resulting components all have values divisible
    // by k, where the value of a component is the sum of the values of all its
    // nodes.
    // Want: the maximum number of components in any valid split. i.e., how
    // many times we can split such that each component is valid.
    //
    // First, note that we are given a Tree. A tree can be disconnected, i.e.,
    // becomes a forest by removing a single edge.
    // No idea bruv. Probably start from bottom up? Something like 2sum?
    // Would be simpler if the edges werent already there.
    // Hm. Something like segment sums?
    // Postorder traversal? If the child is already a multiple, then disconnect
    // the child. Else, include the parent and/or the sibling.
    //
    // Still tough though, considering we are given the edges and not the
    // adjList, with no clear tree structure for traversal.
    // But the above observation seems to be correct, where given a
    // terminal/leaf node, if its value is already a multiple, then disconnect
    // it from its parent.
    // Else, connect it with its parent.
    //
    // NOTE: A tree can be rooted at any node, making things simpler.
    // We can root the Tree at node 0, then do somewhat of a level-order
    // traversal, involving a visited set, so we know which are the parents (a
    // child would have already been visited).
    std::vector<std::vector<int>> adjList(n);

    // Should have n-1 edges.
    for (const auto& edge : edges) {
      adjList[edge[0]].push_back(edge[1]);
      adjList[edge[1]].push_back(edge[0]);
    }

    std::vector<bool> visited(n, false);
    int components = 0;

    // root component
    i64 sum = postorder(adjList, values, k, visited, 0, components);
    if (sum % k == 0) {
      ++components;
    }

    return components;
  }
};
