#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <utility>
#include <vector>

class Solution {
 public:
  int minimumDiameterAfterMerge(std::vector<std::vector<int>>& edges1,
                                std::vector<std::vector<int>>& edges2) {
    // i HATE tree problems :<
    // diameter: length of the longest path between any two nodes.
    //
    // edges[i] = [a, b].
    // Want: connect tree1 to tree2 with an Edge, such that the resulting tree
    // has the minimum possible diameter.
    // Hm. Find diameter of both trees (and their respective nodes),
    // and connect them there? Almost! Connect them NOT at their ends, but in
    // the middle. Is this the optimal way to connect both Trees?
    //
    // WARNING:
    // The resulting minimum diameter may be equal to either diameter(tree1)
    // or diameter(tree2), if either of these diameter are shorter than the
    // resulting diameter of the combined trees.
    // Also, diameter is the longest path between any two nodes. A little
    // confusingly worded with minimum, implying that a tree may have multiple
    // diameters, but really its just the minimum of all the possible ways to
    // add an edge.
    //
    // Wew. How?
    // Given that we only want the resulting minimum diameter, we do not have to
    // keep track of the middle node of the minimum diameter of either tree.
    // Just take the ceiling of both, add 1.
    //
    // In Binary Trees, a complete search is necessary. Probably the same here,
    // root the tree at an arbitrary node, and do a DFS.
    const int n = edges1.size() + 1;  // +1 since a Tree has n-1 edges.
    const int m = edges2.size() + 1;

    auto processEdges = [](const std::vector<std::vector<int>>& edges)
        -> std::vector<std::vector<int>> {
      std::vector<std::vector<int>> adj(edges.size() + 1);
      for (const auto& edge : edges) {
        adj[edge[0]].push_back(edge[1]);
        adj[edge[1]].push_back(edge[0]);
      }
      return adj;
    };

    std::vector<std::vector<int>> adj1 = processEdges(edges1);
    std::vector<std::vector<int>> adj2 = processEdges(edges2);

    auto [discard1, diameter1] = getDiameter(adj1, 0, -1);
    auto [discard2, diameter2] = getDiameter(adj2, 0, -1);

    int combined = ((diameter1 + 1) / 2) + ((diameter2 + 1) / 2) + 1;

    return std::max(combined, std::max(diameter1, diameter2));
  }

 private:
  std::pair<int, int> getDiameter(std::vector<std::vector<int>>& adj,
                                  int i,
                                  int parent) {
    // For a Binary Tree, maintain both current diameter, and the global
    // maximum.
    // For trees with arbitrary number of children, similar.
    // Need multiple information:
    // - Length of path from leaves, ENDING at THIS node.
    // - Length of path from leave to another leave, PASSING through THIS node.
    //
    // For the first, the longest child path can be used.
    // For the second, two of the longest child paths need to be used.
    int maxDepth = 0;
    int secondMaxDepth = 0;
    int maxChildDiameter = 0;
    for (int child : adj[i]) {
      if (child == parent) {
        continue;
      }

      auto [depth, childDiameter] = getDiameter(adj, child, i);
      maxChildDiameter = std::max(maxChildDiameter, childDiameter);

      depth += 1;  // include current node

      if (depth > maxDepth) {
        secondMaxDepth = maxDepth;
        maxDepth = depth;
      } else if (depth > secondMaxDepth) {
        secondMaxDepth = depth;
      }
    }

    int diameterThroughNode = maxDepth + secondMaxDepth;
    return {maxDepth, std::max(diameterThroughNode, maxChildDiameter)};
  }
};
