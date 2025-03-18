#include <cstddef>
#include <cstdlib>
#include <queue>
#include <vector>

class Solution {
 public:
  std::vector<int> shortestDistanceAfterQueries(
      int n,
      std::vector<std::vector<int>>& queries) {
    // Something like dp[i] represents the length of the shortest path from
    // node i to node n-1.
    // Then for each query [u ,v],
    // dp[u] = min(dp[u], dp[v] + 1)
    // But for i < u, dp[i] needs to be updated too.
    // Something like dp[i] = min(dp[i], dp[i+1])?
    // Try walking through an example?
    // n = 5, queries = [[2,4],[0,2],[0,4]]
    // dp = [4, 3, 2, 1, 0]
    //
    // iter1 => dp = [4, 3, 1, 1, 0] // process query
    //          dp = [3, 2, 1, 1, 0] // update dp[i] for i < u
    //
    // iter2 => dp = [2, 2, 1, 1, 0]
    //
    // iter3 => dp = [1, 2, 1, 1, 0]
    // Seems to work. Time complexity is roughly O(qn), q is number of queries.
    //
    // n = 6, queries = [[1,3],[3,5]]
    // dp = [5, 4, 3, 2, 1, 0]
    // iter1 => dp = [5, 3, 3, 2, 1, 0]
    //          dp = [4, 3, 3, 2, 1, 0]
    // iter2 => dp = [5, 3, 3, 1, 1, 0]
    //          dp = [4, 3, 2, 1, 1, 0] WRONG. Does not account for [1, 3]
    //
    // What about just BFS every query.
    // Initially there are n-1 edges. Each query adds one edge. So our time
    // complexity for each BFS is at most O(n + q).
    // q queries means O(q(n+q))
    std::vector<std::vector<int>> adjList(n);
    for (int i = 0; i < n - 1; ++i) {
      adjList[i].push_back(i + 1);
    }

    std::vector<int> result;
    result.reserve(queries.size());
    for (const auto& query : queries) {
      adjList[query[0]].push_back(query[1]);

      result.push_back(bfs(adjList, 0, n - 1));
    }
    return result;
  }

 private:
  int bfs(std::vector<std::vector<int>>& adjList, int src, int dest) {
    std::vector<char> visited(adjList.size(), false);
    std::queue<int> frontier;
    frontier.push(src);
    visited[src] = true;

    int steps = 0;
    while (!frontier.empty()) {
      int n = frontier.size();
      while (n--) {
        int curr = frontier.front();
        frontier.pop();

        if (curr == dest) {
          return steps;
        }

        for (int next : adjList[curr]) {
          if (visited[next]) {
            continue;
          }

          frontier.push(next);
          visited[next] = true;
        }
      }
      ++steps;
    }
    return steps;
  }
};
