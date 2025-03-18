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

class Solution {
 public:
  bool canFinish(int numCourses, std::vector<std::vector<int>>& prerequisites) {
    // prerequisites[i] = [ai, bi] such that bi must be taken before ai
    // Implies some form of topological sort.
    // Sort [0..numCourses] such that courses that have to be taken
    // first is in front.
    std::vector<int> sortedCourses = topologicalSort(numCourses, prerequisites);

    return sortedCourses.size() == numCourses;
  }

 private:
  std::vector<int> topologicalSort(
      int numCourses,
      const std::vector<std::vector<int>>& prerequisites) {
    std::vector<std::vector<int>> adjacencyList(numCourses);
    std::vector<int> inDegree(numCourses, 0);

    // Form adjacencyList and update inDegree of courses
    // if course A has an directed edge to course B, then course A is a
    // prerequisite of B
    for (const auto& prerequisite : prerequisites) {
      int from = prerequisite[1];  // course B must be taken before course A
      int to = prerequisite[0];

      adjacencyList[from].push_back(to);
      ++inDegree[to];
    }

    std::queue<int> zeroIn;
    for (int i = 0; i < numCourses; ++i) {
      if (!inDegree[i]) {
        zeroIn.push(i);
      }
    }
    // Pop nodes with zero inDegree, update its neighbours, and add nodes with
    // zero inDegree. Repeat until queue is empty
    std::vector<int> result;
    result.reserve(numCourses);
    while (!zeroIn.empty()) {
      int curr = zeroIn.front();
      zeroIn.pop();

      result.push_back(curr);
      for (const auto& neighbour : adjacencyList[curr]) {
        --inDegree[neighbour];
        if (!inDegree[neighbour]) {
          zeroIn.push(neighbour);
        }
      }
    }

    if (result.size() < numCourses) {
      return {};  // Cycle detected
    }

    return result;
  }
};
