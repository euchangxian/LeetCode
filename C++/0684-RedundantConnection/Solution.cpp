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

public:
  UnionFind(int n) : parent(n), rank(n) {
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

    if (rank[rootX] < rank[rootY]) {
      parent[rootX] = parent[rootY];
      ++rank[rootY];
    } else {
      if (rank[rootX] == rank[rootY]) {
        ++rank[rootX];
      }
      parent[rootY] = parent[rootX];
    }
  }
};

class Solution {
public:
  vector<int> findRedundantConnection(vector<vector<int>> &edges) {
    int n = edges.size();
    UnionFind uf(n + 1); // extra 0, since 1-indexed

    for (auto const &edge : edges) {
      int a = edge[0];
      int b = edge[1];

      if (uf.connected(a, b)) {
        return edge;
      }

      uf.unite(a, b);
    }

    // Should not reach here.
    return {};
  }
};
