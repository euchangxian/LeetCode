#include <algorithm>
#include <string>
#include <string_view>
#include <vector>

class Solution {
private:
  int32_t dfs(const std::vector<std::vector<size_t>> &adjList,
              const std::string_view &s, int32_t &result, size_t curr) {
    // Returns the longest path that ENDS at the current node.
    // This is because a path that does not end at the current node will not
    // be useful for parent nodes. It will be disconnected.
    //
    // However, we still want to know the longest path that INCLUDES the current
    // node. This is because the resulting longest path does not necessarily
    // involve the parent node.
    // To do this, we will need to consider TWO child paths. WLOG, one that ends
    // with the current node, and one that starts at the current node. This
    // will give us the length of the longest path that includes the
    // current node.

    // chain1 is the longest path that ends/starts with this node.
    int32_t chain1{0};

    // chain2 is the second longest path that ends/starts with this node
    int32_t chain2{0};
    for (const size_t &child : adjList[curr]) {
      const int32_t childPathLength = dfs(adjList, s, result, child);

      if (s[curr] == s[child]) {
        // The childPath will not include the current node.
        continue;
      }

      if (childPathLength > chain1) {
        // Update the top 2 longest paths
        chain2 = chain1;
        chain1 = childPathLength;
        continue;
      }

      if (childPathLength > chain2) {
        // Only the second-longest need to be updated
        chain2 = childPathLength;
      }
    }

    // Update the global longest path.
    result = std::max(result, chain1 + 1 + chain2);
    return 1 + chain1;
  }

public:
  int longestPath(std::vector<int> &parent, std::string s) {
    const size_t n = parent.size();

    // Process the parent vector to create an adjacency list.
    std::vector<std::vector<size_t>> adjList(n);
    for (size_t i = 1; i < parent.size(); ++i) {
      adjList[parent[i]].push_back(i);
    }

    // The Longest Path does not need to involve the root node.
    int32_t result{0};
    dfs(adjList, s, result, 0);
    return result;
  }
};
