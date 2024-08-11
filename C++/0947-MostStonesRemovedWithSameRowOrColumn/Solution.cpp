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
  UnionFind(int size) : parent(size), rank(size) {
    for (int i = 0; i < size; ++i) {
      parent[i] = i;
    }
  }

  int find(int x) {
    if (parent[x] != x) {
      parent[x] = find(parent[x]);
    }
    return parent[x];
  }

  bool isConnected(int x, int y) { return find(x) == find(y); }

  void unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY) {
      return;
    }

    if (rank[rootX] < rank[rootY]) {
      parent[rootX] = parent[rootY];
    } else {
      parent[rootY] = parent[rootX];
      if (rank[rootX] == rank[rootY]) {
        ++rank[rootX];
      }
    }
  }
};

class Solution {
private:
  const int MAX_XY = 10001;

public:
  int removeStones(vector<vector<int>> &stones) {
    if (stones.size() < 2) {
      return 0;
    }

    // 0 <= xi, yi <= 10^4
    UnionFind uf(MAX_XY * 2);
    for (auto const &stone : stones) {
      int r = stone[0];
      int c = stone[1];

      // Offset column index
      // This can be a little unintuitive, where the row index of a stone is
      // unioned with its column index. but this ensures that subsequent stones
      // with either the same row or column index are connected by an edge with
      // the inserted stone.
      uf.unionSets(r, c + MAX_XY);
    }

    unordered_set<int> uniqueRoots;
    for (const auto &stone : stones) {
      uniqueRoots.insert(uf.find(stone[0]));
    }

    return stones.size() - uniqueRoots.size();
  }
};
