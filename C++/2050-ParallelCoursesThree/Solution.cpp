#include <algorithm>
#include <queue>
#include <utility>
#include <vector>

class Solution {
 public:
  int minimumTime(int n,
                  std::vector<std::vector<int>>& relations,
                  std::vector<int>& time) {
    // n courses labelled 1 to n.
    // relations[j] = [prev, next] indicate prev has to be done before next.
    // time[i] indicate how many months it takes to complete the (i+1)th course.
    // - A course can be taken once its prerequisites has been fulfilled
    // - Any number of courses can be taken at the same time.
    //
    // Topological sort. Then BFS. If a course's indegree is 0, that indicates
    // it can be taken at the current time.
    // Ah. We need a `latestTime` seen for the course.
    std::vector<std::vector<int>> adj(n);
    std::vector<int> indegree(n, 0);
    for (const auto& edge : relations) {
      // convert to 0-index
      int u = edge[0] - 1, v = edge[1] - 1;
      adj[u].push_back(v);
      ++indegree[v];
    }

    // {courseIdx, timeFinished}, where timeFinished will be used to determine
    // the next course time.
    std::queue<std::pair<int, int>> frontier;
    for (int i = 0; i < n; ++i) {
      if (indegree[i] == 0) {
        frontier.emplace(i, time[i]);
      }
    }

    std::vector<int> latest(n, 0);
    int completionTime = 0;
    while (!frontier.empty()) {
      auto [curr, currTime] = frontier.front();
      frontier.pop();
      completionTime = std::max(completionTime, currTime);

      for (int next : adj[curr]) {
        latest[next] = std::max(latest[next], currTime);
        if (--indegree[next] == 0) {  // all prerequisites fulfilled.
          frontier.emplace(next, latest[next] + time[next]);
        }
      }
    }
    return completionTime;
  }
};
