#include <queue>
#include <vector>

class Solution {
 public:
  std::vector<int> findOrder(int numCourses,
                             std::vector<std::vector<int>>& prerequisites) {
    // Similar to CourseScheduleOne. Topological sort and return the order
    return topologicalSort(numCourses, prerequisites);
  }

 private:
  std::vector<int> topologicalSort(
      int numCourses,
      const std::vector<std::vector<int>>& prerequisites) {
    std::vector<std::vector<int>> adj(numCourses);
    std::vector<int> inDegrees(numCourses, 0);

    for (const auto& prerequisite : prerequisites) {
      // (a, b) => directed edge from b to a
      int from = prerequisite[1];
      int to = prerequisite[0];

      adj[from].push_back(to);
      ++inDegrees[to];
    }

    std::queue<int> zeroes;
    for (int i = 0; i < numCourses; ++i) {
      if (inDegrees[i] == 0) {
        zeroes.push(i);
      }
    }

    std::vector<int> result;
    result.reserve(numCourses);
    while (!zeroes.empty()) {
      int curr = zeroes.front();
      zeroes.pop();
      result.push_back(curr);

      for (int neighbour : adj[curr]) {
        if (--inDegrees[neighbour] == 0) {
          zeroes.push(neighbour);
        }
      }
    }

    if (result.size() < numCourses) {
      return {};
    }
    return result;
  }
};
