#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class Solution {
 private:
  vector<int> topologicalSort(int const& numCourses,
                              vector<vector<int>> const& prerequisites) {
    vector<vector<int>> adj(numCourses);
    vector<int> inDegrees(numCourses, 0);

    for (auto const& prerequisite : prerequisites) {
      // (a, b) => directed edge from b to a
      int from = prerequisite[1];
      int to = prerequisite[0];

      adj[from].push_back(to);
      ++inDegrees[to];
    }

    queue<int> zeroes;
    for (int i = 0; i < numCourses; ++i) {
      if (inDegrees[i] == 0) {
        zeroes.push(i);
      }
    }

    vector<int> result;
    result.reserve(numCourses);
    while (!zeroes.empty()) {
      int curr = zeroes.front();
      zeroes.pop();
      result.push_back(curr);

      for (auto const& neighbour : adj[curr]) {
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

 public:
  vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    // Similar to CourseScheduleOne. Topological sort and return the order
    return topologicalSort(numCourses, prerequisites);
  }
};
