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
  vector<int> topologicalSort(int const &numCourses,
                              vector<vector<int>> const &prerequisites) {
    vector<vector<int>> adjacencyList(numCourses);
    vector<int> inDegree(numCourses, 0);

    // Form adjacencyList and update inDegree of courses
    // if course A has an directed edge to course B, then course A is a
    // prerequisite of B
    for (auto const &prerequisite : prerequisites) {
      int from = prerequisite[1]; // course B must be taken before course A
      int to = prerequisite[0];

      adjacencyList[from].push_back(to);
      ++inDegree[to];
    }

    queue<int> zeroIn;
    for (int i = 0; i < numCourses; ++i) {
      if (!inDegree[i]) {
        zeroIn.push(i);
      }
    }
    // Pop nodes with zero inDegree, update its neighbours, and add nodes with
    // zero inDegree. Repeat until queue is empty
    vector<int> result;
    result.reserve(numCourses);
    while (!zeroIn.empty()) {
      int curr = zeroIn.front();
      zeroIn.pop();

      result.push_back(curr);
      for (auto const &neighbour : adjacencyList[curr]) {
        --inDegree[neighbour];
        if (!inDegree[neighbour]) {
          zeroIn.push(neighbour);
        }
      }
    }

    if (result.size() < numCourses) {
      return {}; // Cycle detected
    }

    return result;
  }

public:
  bool canFinish(int numCourses, vector<vector<int>> &prerequisites) {
    // prerequisites[i] = [ai, bi] such that bi must be taken before ai
    // Implies some form of topological sort.
    // Sort [0..numCourses] such that courses that have to be taken
    // first is in front.
    vector<int> sortedCourses = topologicalSort(numCourses, prerequisites);

    return sortedCourses.size() == numCourses;
  }
};
