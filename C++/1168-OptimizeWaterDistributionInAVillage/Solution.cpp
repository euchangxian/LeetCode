#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <tuple>
#include <utility>
#include <vector>

class UnionFind {
 public:
  UnionFind(int n) : components_(n), parent_(n), rank_(n, 0), size_(n, 1) {
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

  void unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY) {
      return;
    }

    --components_;
    if (rank_[rootX] < rank_[rootY]) {
      parent_[rootX] = rootY;
      size_[rootY] += std::exchange(size_[rootX], 0);
      return;
    }

    if (rank_[rootX] == rank_[rootY]) {
      ++rank_[rootX];
    }
    parent_[rootY] = rootX;
    size_[rootX] += std::exchange(size_[rootY], 0);
  }

  int components() const noexcept { return components_; }

  int size(int x) { return size_[find(x)]; }

 private:
  int components_;

  std::vector<int> parent_;
  std::vector<int> rank_;
  std::vector<int> size_;
};

class Solution {
 public:
  int minCostToSupplyWater(int n,
                           std::vector<int>& wells,
                           std::vector<std::vector<int>>& pipes) {
    // n houses.
    // Cost of building a well at ith house is wells[i]
    // Cost of connecting two houses u, v is given by pipes[i] = [u, v, cost]
    // Return minimum cost to connect all houses to a well.
    //
    // Note that there can be multiple edges with the same src, dest, but
    // different cost. I suppose those are redundant, only keep same ones.
    // No self-edges.
    //
    // What is the optimal strategy here?
    // Decision is probably to determine whether the cost of building a well,
    // or connecting this house to some other well is cheaper.
    // Also, note that the resultant graph may be a forest? E.g., cost of
    // building wells in every house is cheaper than connecting any of them.
    //
    // Is it correct to assume that the global minimum cost of wells will
    // always be taken? i.e., sort by cost of well, then always build in that
    // min cost?
    //
    // Should be. There should not be a notion of a "central/star" node since
    // we just need connected components.
    // Then, can we just root the tree at the lowest cost, connect houses
    // until the connection cost is greater than simply building?
    //
    // Hm. What about creating the graph itself first.
    // Nodes as Houses, Edges as in Pipes.
    // What about well costs? Create a virtual well node. Connect to the houses
    // by the cost indicated by wells[i].
    //
    // Which algorithm! MST. Wow. Kruskals!
    // Let node0 be the well. Then houses are 1-indexed just like in pipes.
    // {cost, u, v}
    std::vector<std::tuple<int, int, int>> edges;
    edges.reserve(wells.size() + pipes.size());
    for (int i = 1; i <= n; ++i) {
      edges.emplace_back(wells[i - 1], 0, i);
    }
    for (const auto& edge : pipes) {
      edges.emplace_back(edge[2], edge[0], edge[1]);
    }

    // ascending cost
    std::sort(edges.begin(), edges.end());

    int total = 0;
    UnionFind G(n + 1);
    for (const auto [cost, u, v] : edges) {
      if (G.connected(u, v)) {
        continue;
      }
      total += cost;
      G.unite(u, v);
    }

    return total;
  }
};
