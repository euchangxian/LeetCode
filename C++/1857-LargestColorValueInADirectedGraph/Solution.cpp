#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdlib>
#include <queue>
#include <string_view>
#include <vector>

class Solution {
 public:
  int largestPathValue(std::string_view colors,
                       std::vector<std::vector<int>>& edges) {
    // Given Directed graph.
    // colors[i] represent the color of the ith node.
    // edges[i] = [u, v] indicating a directed edge from u to v.
    //
    // Want: the largest colour value among all valid paths, where a
    // valid path is a sequence of nodes x1 -> x2 -> ... -> xk such that
    // there is a directed edge from xi to xi+1 for every node in the path.
    //
    // The color value is the frequency of the most colored color in the path.
    //
    // At first glance, seemed like topological sort. Allows us to find any
    // possible cycles.
    // But this does not give us the valid paths and their color values.
    // What about topological sort + DFS? Since we have the root nodes, we can
    // DFS from the root nodes.
    //
    // For DFS, maintain the frequency of the occurence of each color.
    // Runtime seems complex though, with plenty of repeated???? work, since
    // we are backtracking the DFS tree. What about memoization/dp?
    // Something like the maximum frequency color at node i.
    // Or the count of colors ending at node i.
    //
    // Note that there are a maximum of 26 distinct colors (lower alphabets).
    // To be more precise, we can maintain dp[i][j], indicating the
    // maximum count of the color j, in any valid paths ending at node i.
    const size_t n = colors.size();

    std::vector<std::vector<int>> adjList(n);
    std::vector<int> indegree(n, 0);
    for (const auto& edge : edges) {
      const int from = edge[0];
      const int to = edge[1];

      adjList[from].push_back(to);
      ++indegree[to];
    }

    // topo sort
    std::queue<int> frontier;
    for (int i = 0; i < n; ++i) {
      if (indegree[i] == 0) {
        frontier.push(i);
      }
    }

    int count = 0;  // nodes count, to determine if there is a cycle.
    int maxColor = 0;

    // dp[node][color] indicate the maximum count of color in any path ending at
    // node.
    std::vector<std::array<int, 26>> dp(n, std::array<int, 26>{});
    while (!frontier.empty()) {
      int curr = frontier.front();
      frontier.pop();
      ++count;

      // process the colors ending at this node.
      ++dp[curr][colors[curr] - 'a'];
      maxColor = std::max(maxColor, dp[curr][colors[curr] - 'a']);

      for (int neighbour : adjList[curr]) {
        // NOTE: for each neighbour, propagate/prepopulate the current maximum
        // color count.
        for (int c = 0; c < 26; ++c) {
          dp[neighbour][c] = std::max(dp[neighbour][c], dp[curr][c]);
        }

        if (--indegree[neighbour] == 0) {
          frontier.push(neighbour);
        }
      }
    }

    if (count != n) {
      return -1;  // cycle
    }
    return maxColor;
  }
};
