#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <queue>
#include <vector>

class UnionFind {
 public:
  UnionFind(int n) : parent_(n), rank_(n, 0) {
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

    if (rank_[rootX] < rank_[rootY]) {
      parent_[rootX] = rootY;
      return;
    }

    if (rank_[rootX] == rank_[rootY]) {
      ++rank_[rootX];
    }
    parent_[rootY] = rootX;
  }

 private:
  std::vector<int> parent_;
  std::vector<int> rank_;
};

class Solution {
 public:
  int magnificentSets(int n, std::vector<std::vector<int>>& edges) {
    // Given edges, where edges[i] = [a, b] indicate a bidirectional edge
    // between nodes a and b.
    //
    // To divide the nodes into groups such that:
    // - Each node belongs to exactly one group,
    // - Every pair of nodes connected by an edge must belong to adjacent
    //   groups, i.e., if a in group X, and b in group Y, then |X - Y| = 1.
    // To maximize the number of groups. -1 if not possible.
    //
    // First glance seems like Topological Sort. But edges are bidirectional.
    // Very similar to Graph Coloring too, i.e., Bipartite Graphs.
    // i.e., no two nodes connected by an edge have the same color. Therefore,
    // only two colours are needed.
    //
    // Suppose we root the graph at an arbitrary node, say 1.
    // Then, start with an arbitrary colour, say Red->Blue. Assign Red, to 1,
    // Blue to all its neighbour, and DFS.
    // If any edges can not be colored different, then it is not possible for
    // Groups to be assigned.
    // At the end, we will have two groups of nodes.
    // How to maximize the number of groups, while still fulfilling the
    // constraints then?
    // How can we detect nodes in the same group, that do not need to be
    // grouped together?
    //
    // Alternatively, what if we brute-force with each node as the root of the
    // Graph? i.e., assign groups corresponding to the node's depth. Seems
    // plausible.
    //
    // WARNING: input graph may not be a single connected component.
    // Thus, there is a need to find the max group of each component.
    // UF can be used to identify which nodes belong to which component.
    UnionFind G(n);
    std::vector<std::vector<int>> adj(n);
    for (const auto& edge : edges) {
      // convert to 0-index.
      adj[edge[0] - 1].push_back(edge[1] - 1);
      adj[edge[1] - 1].push_back(edge[0] - 1);
      G.unite(edge[0] - 1, edge[1] - 1);
    }

    // return -1 if the depths are not consecutive.
    auto bfs = [n, &adj](int src) -> int {
      // distance from the root.
      std::vector<int> color(n, -1);
      std::queue<int> frontier{{src}};
      color[src] = 0;

      // Need to ensure nodes connected by an edge have
      // |depth[u] - depth[v]| = 1
      // Checks need to be done when "revisiting" nodes.
      int currColor = 1;
      int distance = 0;
      while (!frontier.empty()) {
        int sz = frontier.size();
        while (sz--) {
          int curr = frontier.front();
          frontier.pop();
          for (int next : adj[curr]) {
            if (color[next] == -1) {
              color[next] = currColor;
              frontier.push(next);
            } else if (color[next] == color[curr]) {
              return -1;  // constraints are violated.
            }
          }
        }
        currColor = 1 - currColor;
        ++distance;
      }

      // No need to +1 to include the root group, should be done in the last
      // iteration.
      return distance;
    };

    std::vector<bool> processed(n, false);
    std::vector<int> componentNumGroups(n, 0);
    int result = 0;
    for (int node = 0; node < n; ++node) {
      int component = G.find(node);
      if (processed[component]) {
        continue;
      }
      processed[component] = true;

      // try each node in THIS component as the root.
      for (int root = 0; root < n; ++root) {
        if (!G.connected(component, root)) {
          continue;
        }

        int depth = bfs(root);
        if (depth == -1) {
          // constraints cannot be fulfilled.
          return -1;
        }

        componentNumGroups[component] =
            std::max(componentNumGroups[component], depth);
      }

      result += componentNumGroups[component];
    }

    return result;
  }
};
