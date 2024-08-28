#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class UnionFind {
private:
  vector<int> parent;
  vector<int> rank;
  vector<int> size;

public:
  UnionFind(int n) : parent(n), rank(n), size(n, 1) {
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

  void unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY) {
      return;
    }

    if (rank[rootX] < rank[rootY]) {
      parent[rootX] = parent[rootY];
      size[rootY] += size[rootX];
      return;
    }

    parent[rootY] = parent[rootX];
    size[rootX] += size[rootY];
    if (rank[rootX] == rank[rootY]) {
      ++rank[rootX];
    }
  }

  int getSize(int x) { return size[find(x)]; }
};

class Solution {
public:
  int countCompleteComponents(int n, vector<vector<int>> &edges) {
    UnionFind uf(n);

    vector<int> edgeCount(n, 0);
    for (auto const &edge : edges) {
      uf.unite(edge[0], edge[1]);

      ++edgeCount[edge[0]];
      ++edgeCount[edge[1]];
    }

    vector<bool> isComplete(n, true);
    for (int i = 0; i < n; ++i) {
      int root = uf.find(i);

      int componentSize = uf.getSize(root);

      // For a component to be complete, each node must have v-1 edges
      if (edgeCount[i] < componentSize - 1) {
        isComplete[root] = false;
      }
    }

    int result = 0;
    for (int i = 0; i < n; ++i) {
      // if root and complete
      if (uf.find(i) == i && isComplete[i]) {
        ++result;
      }
    }

    return result;
  }
};
