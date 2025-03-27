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
  std::vector<int> findRedundantDirectedConnection(
      std::vector<std::vector<int>>& edges) {
    // Directed Graph, edges[i] = [a, b] represent a directed edge from a to b.
    // Find an edge that can be removed so that the resultant graph is a rooted
    // tree of n nodes.
    // i.e., no cycles.
    // Not entirely sure how different this is from the undirected variant.
    // What difference is a rooted tree from a tree?
    //
    // Oh. LOL. read the question.
    // A rooted tree is a directed graph for which there is exactly one root
    // node, and every other node are descendents of this root.
    // Also, every other node has exactly one parent.
    //
    // Naively uniting every node in order of the edges and checking for edges
    // that create a cycle does not work.
    // It only fulfils the no-cycle constraint and not the rooted constraints.
    //
    // First, if indegree[u] > 1, we need to fix that, as it indicates that node
    // u has more than 1 parent.
    // Is this sufficient??? LOL. Proof by AC?
    //
    // Nope, still need to fulfil no-cycle.
    // Hmmmm.
    // Doing two passes; one to check indegree, then the other to check cycles,
    // will also not work. There are three possible cases:
    // 1. two-parents, i.e., indegree[u] == 2, then remove the extra edge (i.e.,
    //    the edge that appears later. Let this extra edge be cand)
    // 2. cycle, i.e., UF (remove the last edge that forms a cycle)
    // 3. two-parents AND cycle, (check if removing the candidate edge removes
    //                            the cycle)
    //
    // E.g., [[1, 2], [2, 3], [3, 1], [4, 3]]
    // Naively doing the indegree check independently of the cycle check and
    // vice-versa will result in the wrong edge (4, 3) being removed, without
    // resolving the cycle 1->2->3->1
    // Doing the cycle check independently will wrongly remove (3, 1), where
    // node 3 still has two parents.
    // The correct answer should be (2, 3), which upon removing, fulfils the
    // constraint of node 3 having one parent, and no cycles.
    //
    // Thus, we need to make both (2, 3) and (4, 3) a candidate edge first.
    // Then check if removing (4, 3), the later occuring one will fulfil our
    // no-cycle constraint.
    const int n = edges.size();
    std::vector<int> parent(n + 1, 0);
    std::vector<int> candidate1, candidate2;
    for (auto& edge : edges) {
      int a = edge[0], b = edge[1];
      if (parent[b] == 0) {
        parent[b] = a;
        continue;
      }

      // 2 parent case
      candidate1 = {parent[b], b};  // the edge that occured earlier
      candidate2 = edge;            // copy
      edge[1] = 0;  // mark this later-occuring edge, so we can skip it later.
    }

    // Then we check for cycles.
    UnionFind G(n + 1);  // extra 0, since 1-indexed
    for (const auto& edge : edges) {
      int a = edge[0];
      int b = edge[1];
      if (b == 0) {
        continue;  // dont add this edge!
      }

      // if there is still a cycle after "removing" the above edge, then we must
      // remove either the above candidate1, or this edge.
      if (G.connected(a, b)) {
        if (candidate1.empty()) {
          return edge;
        }
        return candidate1;
      }

      G.unite(a, b);
    }

    return candidate2;
  }
};
