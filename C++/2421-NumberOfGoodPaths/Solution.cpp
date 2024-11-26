#include <cstddef>
#include <cstdlib>
#include <map>
#include <unordered_map>
#include <vector>

class UnionFind {
 private:
  std::vector<int> parent;
  std::vector<int> rank;

 public:
  UnionFind(const size_t n) : parent(n), rank(n, 0) {
    for (int i = 0; i < n; ++i) {
      parent[i] = i;
    }
  }

  int find(int x) {
    if (parent[x] != x) {
      parent[x] = find(parent[x]);
    }

    return parent[x];
  }

  bool connected(int x, int y) { return find(x) == find(y); }

  void unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY) {
      return;
    }

    // union by rank.
    if (rank[rootX] < rank[rootY]) {
      parent[rootX] = parent[rootY];
      return;
    }

    if (rank[rootX] == rank[rootY]) {
      ++rank[rootX];
    }
    parent[rootY] = parent[rootX];
  }
};

class Solution {
 private:
  static constexpr int MAX_VAL = 100'000;

 public:
  int numberOfGoodPaths(std::vector<int>& vals,
                        std::vector<std::vector<int>>& edges) {
    // Hm. Given a Tree with n nodes numbered 0 to n-1.
    // Find number of Good Paths.
    //
    // Good Paths are paths whose Start and End nodes have the same value, and
    // every node in between have values LTE the Start node.
    //
    // First observation: Tree. This means that for any pair of nodes u, v,
    // there exist only a single path between them.
    //
    // Trees have no cycles, and with N nodes, there are N-1 edges. Does this
    // help?
    //
    // Would counting the number of nodes with value x be helpful?
    // If there is only one node with value x, then there is no need to check
    // for further Good Paths starting from that node.
    // Naively, once the count is done, for each pair of a specific value,
    // check if a Good Path exists, i.e,. all the nodes in between are LTE.
    // O(n^2) already, if all the nodes have the same value.
    // Input constraints n <= 3*10^4 rule out such a solution.
    //
    // Can we do better though?
    // Something like iterating from the maximum values first? Since it is
    // guaranteed that there is no greater-value node in the pairs.
    //
    // But what about subsequent lower-valued Paths? Are we able to efficiently
    // check if any of the previous higher-valued nodes are inside the path
    // between pairs?
    //
    // Hmmmmmm. What about iterating from smallest value first?
    // This allows us to use UnionFind (note: gap in intuition is kinda big).
    //
    // We start from value=1. If there is more than 1 node with value=1, then
    // we start from any value=1 nodes, and union neighbouring nodes that have
    // value <= 1.
    //
    // But how do we count the number of Good Paths? By counting the number of
    // nodes in their connected component i.e., combinatorics?
    // Combinatorics is correct. But more specifically, for the current value
    // in consideration, we want to count the number of same-valued nodes in
    // the same component. The Tree property that a single path exists between
    // each pair still holds.
    // i.e., if the group has 3 value=1 nodes, then the number of Good Paths is
    // 3 * (3 + 1)/2 = 6 (3 trivial paths of length 0.)
    const size_t n = vals.size();

    // create adjList to identify neighbours fast.
    std::vector<std::vector<int>> adjList(n);
    for (const auto& edge : edges) {
      adjList[edge[0]].push_back(edge[1]);
      adjList[edge[1]].push_back(edge[0]);
    }

    // group nodes
    std::map<int, std::vector<int>> nodesByValue;
    for (int i = 0; i < n; ++i) {
      nodesByValue[vals[i]].push_back(i);
    }

    UnionFind uf(n);
    int goodPaths = 0;
    for (const auto& [val, nodes] : nodesByValue) {
      for (int node : nodes) {
        // union neighbours if they have values <= val.
        for (int neighbour : adjList[node]) {
          if (vals[neighbour] <= val) {
            uf.unite(node, neighbour);
          }
        }
      }

      // The core of this is here: For the current value, count the size of
      // the components.
      std::unordered_map<int, int> groupSize;
      for (int node : nodes) {
        int group = uf.find(node);
        ++groupSize[group];
      }

      for (const auto& [_, sz] : groupSize) {
        goodPaths += sz * (sz + 1) / 2;
      }
    }
    return goodPaths;
  }
};
