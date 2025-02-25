#include <climits>
#include <cstddef>
#include <cstdlib>
#include <utility>
#include <vector>

class UnionFind {
 public:
  UnionFind(int n)
      : components_(n), parent_(n), rank_(n, 0), cost_(n, INT_MAX) {
    for (int i = 0; i < n; ++i) {
      parent_[i] = i;
    }
  }

  int find(int x) {
    if (parent_[x] != x) {
      parent_[x] = find(parent_[x]);
    }

    return parent_[x];
  }

  bool connected(int x, int y) { return find(x) == find(y); }

  void unite(int x, int y, int weight) {
    int rootX = find(x);
    int rootY = find(y);

    // NOTE: Early return is removed, to account for multiple edges between
    // the same pair of nodes.
    // if (rootX == rootY) {
    //   return;
    // }

    --components_;
    if (rank_[rootX] < rank_[rootY]) {
      parent_[rootX] = rootY;
      cost_[rootY] &= weight & std::exchange(cost_[rootX], INT_MAX);
      return;
    }

    if (rank_[rootX] == rank_[rootY]) {
      ++rank_[rootX];
    }
    parent_[rootY] = rootX;
    cost_[rootX] &= weight & std::exchange(cost_[rootY], INT_MAX);
  }

  int components() const noexcept { return components_; }

  int cost(int x) { return cost_[find(x)]; }

 private:
  int components_;

  std::vector<int> parent_;
  std::vector<int> rank_;
  std::vector<int> cost_;
};

class Solution {
 public:
  std::vector<int> minimumCost(int n,
                               std::vector<std::vector<int>>& edges,
                               std::vector<std::vector<int>>& query) {
    // edges[i] = [u, v, w], bidirectional edge between u and v with weight w.
    // query[i] = [s, t]
    // answer[i] = min cost of walk starting at node s, ending at node t.
    //
    // At first glance, seems like APSP, where the shortest weight from s to t
    // is necessary to answer the queries.
    // But clearly that will TLE.
    // Instead, notice that the cost of the walk is defined as the bitwise AND.
    // One key property is that adding more edge weights will only DECREASE the
    // total cost.
    // Thus, we can reduce this problem elegantly to simply finding the total
    // bitwise AND of each connected component, as that will give us the min
    // cost walk.
    UnionFind G(n);
    for (const auto& edge : edges) {
      int u = edge[0], v = edge[1], w = edge[2];
      G.unite(u, v, w);
    }

    std::vector<int> answer;
    answer.reserve(n);
    for (const auto& q : query) {
      int s = q[0], t = q[1];
      if (!G.connected(s, t)) {
        answer.push_back(-1);
      } else {
        answer.push_back(G.cost(s));
      }
    }
    return answer;
  }
};
