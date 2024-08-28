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
  int components;

public:
  UnionFind(int n) : parent(n), rank(n), components(n) {
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
      parent[rootX] = parent[rootY];
      return;
    }

    parent[rootY] = parent[rootX];
    if (rank[rootX] == rank[rootY]) {
      ++rank[rootX];
    }
  }

  int getComponents() { return components; }
};

class Solution {
public:
  bool validTree(int n, vector<vector<int>> &edges) {
    UnionFind uf(n);

    for (auto const &edge : edges) {
      int first = edge[0];
      int second = edge[1];

      if (uf.connected(first, second)) {
        // cycle detection
        return false;
      }

      uf.unite(first, second);
    }

    return uf.getComponents() == 1;
  }
};
