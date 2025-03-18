#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <vector>

class UnionFind {
 public:
  UnionFind(int n) : parent(n), rank(n, 0), components(n) {
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

    --components;
    if (rank[rootX] < rank[rootY]) {
      parent[rootX] = rootY;
      return;
    }

    if (rank[rootX] == rank[rootY]) {
      ++rank[rootX];
    }
    parent[rootY] = rootX;
  }

  int size() { return components; }

 private:
  std::vector<int> parent;
  std::vector<int> rank;
  int components;
};

class Solution {
 public:
  int earliestAcq(std::vector<std::vector<int>>& logs, int n) {
    // Definitely a graph question. Each person is a node. Start from the
    // earliest timestamp. BFS and record the maximum timestamp encountered.
    // At the end, check that the number of nodes encountered is equal to the
    // number of unique nodes, n. Seems to be nlogn + n + E.
    // Can we do better? Union Find, record the maximum timestamp encountered
    // still. At the end, check the number of disjoint sets.
    // Sorting is unavoidable, since we want to process earlier edges first.
    std::sort(logs.begin(), logs.end());
    int earliestTime = 0;
    UnionFind uf(n);
    for (const auto& log : logs) {
      earliestTime = log[0];
      int x = log[1];
      int y = log[2];

      uf.unite(x, y);
      if (uf.size() == 1) {
        break;
      }
    }

    return uf.size() == 1 ? earliestTime : -1;
  }
};
