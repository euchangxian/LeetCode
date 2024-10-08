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
 public:
  // The key insight here is that an island can be disconnected with three ways:
  // 1. If the island is already disconnect (0 days)
  // 2. If theres only one land cell (1 day, remove the land cell)
  // 3. If there is an articulation point (1 day, remove the articulation point)
  // 4. Otherwise, two land cells need to be removed (visualise with diagram,
  //    remove corners)
  //
  // An Articulation Point in a Graph is a vertex V such that removing V
  // increases the number of connected components.
  //
  // To find articulation points, a naive way would be to iterate over all the
  // vertices, and for each vertex v:
  // 1. Remove v from the graph
  // 2. See if the number of connected components increases using DFS / Union
  //    Find
  // 3. Add v back to the graph
  //
  // Time Complexity: O(V * (V + E))
  //
  // A better way is described by Tarjan's Algorithm, which uses DFS.
  // In the DFS tree, a vertex u is an articulation point if either:
  // 1. u is the root of the DFS tree and has at least two children, OR
  // 2. u is NOT the root, and it has a child v such that no vertex in the
  //    subtree rooted at v has a back edge to an ancestor of u (i.e., the
  //    lowest reachable time of v is greater than or equal to the discovery
  //    time of u, or that there is no shorter path from v to an ancestor that
  //    does not go through the intermediate vertex u).
  //
  // To do this, perform a DFS traversal of the graph. For each vertex, three
  // pieces of information is kept:
  // 1. Discovery time:  When the vertex was discovered during DFS. Measured in
  //    number of steps / edges traversed so far (NOT edges to the vertex)
  // 2. Lowest reachable time: The earliest discovered vertex that can be
  //    reached from the subtree rooted at this vertex.
  // 3. Parent: The vertex from which this vertex is discovered.
  //
  // This is because as DFS is performed, a tree is built. For each vertex, we
  // look at all its neighbours:
  // 1. If a neighbour has not been visited, we recurse on it.
  // 2. If a neighbour has been visited and its not the parent, then we know
  //    that its a back edge in the DFS tree.
  //
  // After exploring all neighbours of a vertex u, we can determine if it's an
  // articulation point:
  // 1. If u is not the root and has a child v where the lowest reachable time
  //    of v is greater than or equal to the discovery time of u, then u is an
  //    articulation point. This means there's no back edge from the subtree
  //    rooted at v to any ancestor of u.
  // 2. If u is the root and has more than one child in the DFS tree, it's an
  //    articulation point.
  int minDays(vector<vector<int>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();

    // Time when a cell is first discovered. Also acts as a `visited` Set
    vector<vector<int>> discoveryTime(rows, vector<int>(cols, -1));

    // Lowest discovery time for any cell reachable from the subtree rooted at
    // this cell
    vector<vector<int>> lowestReachableTime(rows, vector<int>(cols, -1));

    // Parent of each cell
    vector<vector<int>> parent(rows, vector<int>(cols, -1));

    // Store 1D coordinates of articulation points. Technically, for this
    // question, a simple boolean flag to indicate whether there is an AP is
    // sufficient to determine the answer
    unordered_set<int> articulationPoints;
    int time = 0;

    int islandCount = 0;  // if 0 or > 2, already disconnected, return 0
    int landCount = 0;    // if 1, return 1

    // For each cell, DFS and update the information
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        if (grid[i][j] == 0) {
          continue;  // Not a vertex
        }

        ++landCount;
        if (discoveryTime[i][j] == -1) {
          // Not visited yet
          // DFS, with the subtree rooted at {i, j}
          findArticulationPoints(grid, discoveryTime, lowestReachableTime,
                                 parent, time, articulationPoints, i, j);
          ++islandCount;
        }
      }
    }

    if (islandCount != 1) {
      return 0;
    }

    if (landCount == 1) {
      return 1;  // only remove that land
    }

    if (!articulationPoints.empty()) {
      return 1;
    }

    return 2;
  }

 private:
  vector<pair<int, int>> const directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

  void findArticulationPoints(vector<vector<int>> const& grid,
                              vector<vector<int>>& discoveryTime,
                              vector<vector<int>>& lowestReachableTime,
                              vector<vector<int>>& parent,
                              int& time,
                              unordered_set<int>& articulationPoints,
                              int const r,
                              int const c) {
    int rows = grid.size();
    int cols = grid[0].size();

    // Update discoveryTime and set lowestReachableTime to current time
    discoveryTime[r][c] = time++;
    lowestReachableTime[r][c] = discoveryTime[r][c];

    // Initialize number of childrens to zero, to be updated in DFS
    int children = 0;

    // Iterate over neighbours of this cell
    for (const auto& [dr, dc] : directions) {
      int nr = r + dr;
      int nc = c + dc;

      if (nr < 0 || nc < 0 || nr >= rows || nc >= cols || grid[nr][nc] == 0) {
        continue;  // if not valid cell, or not land cell
      }

      if (discoveryTime[nr][nc] != -1) {
        // Neighbour is an ancestor, update lowestReachableTime
        lowestReachableTime[r][c] =
            min(lowestReachableTime[r][c], discoveryTime[nr][nc]);
        continue;
      }

      // Otherwise, neighbour is an undiscovered children
      ++children;
      parent[nr][nc] = r * cols + c;

      // Recurse on children
      findArticulationPoints(grid, discoveryTime, lowestReachableTime, parent,
                             time, articulationPoints, nr, nc);

      // Update lowest reachable time of this cell
      lowestReachableTime[r][c] =
          min(lowestReachableTime[r][c], lowestReachableTime[nr][nc]);

      // Check for Articulation Point condition of this cell, if its non-root,
      // its children would have a greater than or equal lowestReachableTime
      // than this cell's discoveryTime.
      if (parent[r][c] != -1 &&
          lowestReachableTime[nr][nc] >= discoveryTime[r][c]) {
        articulationPoints.insert(r * cols + c);
      }
    }

    // Once the subtree rooted at this cell has been explored, we can check the
    // root vertex condition
    if (parent[r][c] == -1 && children > 1) {
      articulationPoints.insert(r * cols + c);
    }
  }
};
