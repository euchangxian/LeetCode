#include <array>
#include <bitset>
#include <cstddef>
#include <cstdlib>
#include <vector>
class Solution {
 public:
  std::vector<bool> checkIfPrerequisite(
      int n,
      std::vector<std::vector<int>>& prerequisites,
      std::vector<std::vector<int>>& queries) {
    // n courses, labelled [0..n-1]
    // prerequisites[i] = [a, b] => a must be taken before b, i.e., in
    // topological order, there is a directed edge from a to b.
    // query[i] = [u, v] => output true if u is a prerequisite of v.
    //
    // Topological sort is straightforward. But it doesnt really allow for
    // quick lookup as to where the node is in the order.
    //
    // Relabelling should work.
    // Ah not exactly. There may be false positives.
    // Consider n=3, prerequisites = {[0, 1]}
    // Then, the order would be something like {[0, 2], [1]}, and it would
    // appear as though node 2 is a prerequisite of 1.
    // Could be solved with UnionFind, but not exactly appropriate since edges
    // are directed.
    // But are there any edge cases?? Yeah...
    // Consider prerequisites = {[0, 2], [0, 3], [1, 2]}. Then, while there
    // is no path from 1 to 3, UF would mark them as connected, since (0, 2)
    // and (1, 2) are present.
    //
    // HOW?? We need to model the relationships (including transitive ones),
    // which kinda involves DFS-ing? I.e., for each node, DFS its neighbouring
    // nodes, and mark them as reachable.
    // Topological Sort is not necessary.
    // O(n^3 + q)...
    //
    // Lol. Floyd Warshall fits this exactly. Should have looked at the
    // constraints. n <= 100 indicates n^3-ish.

    // reachable[u][v] indicates v is reachable from u.
    std::array<std::bitset<101>, 101> reachable{};
    for (const auto& edge : prerequisites) {
      reachable[edge[0]][edge[1]] = true;
    }

    for (int k = 0; k < n; ++k) {
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          reachable[i][j] =
              reachable[i][j] || reachable[i][k] && reachable[k][j];
        }
      }
    }

    std::vector<bool> answer;
    answer.reserve(n);
    for (const auto& query : queries) {
      int u = query[0], v = query[1];
      answer.push_back(reachable[u][v]);
    }
    return answer;
  }
};
