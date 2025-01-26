#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <queue>
#include <vector>

class Solution {
 public:
  int maximumInvitations(std::vector<int>& favorite) {
    // n employees labelled [0..n-1].
    // favorite[i] indicates the favourite person of the ith employee.
    // An employee will only attend the meeting if they can sit beside their
    // favorite person. The table is round.
    // Want: maximum number of employees invited.
    //
    // Hm. Notice that if we have a cycle of size > 2, then no other employees
    // outside of the cycle can be invited, as it would break the cycle.
    //
    // If employees can be paired, i.e., favorite[i] = j and favorite[j] = i,
    // i.e., a cycle of size 2, multiple of such cycles can be placed.
    //
    // The longest possible arrangement would then a n-length cycle,
    // e.g., favorite[0] = 1, favorite[1] = 2, ..., favorite[n-1] = 1.
    // or a linked list ending in a 2-length cycle,
    // e.g., favorite[0] = 1, ..., favorite[n-2] = n-1, favorite[n-1] = n-2.
    //
    // Not exactly. Both ends of the 2-length cycle can be used, like:
    // favorite[0]=1, ... favourite[a]=b, favourite[b]=a, ..., favorite[n-2]=n
    //
    // i.e., max{k-length cycle, x-length list + 2 + y-length list}
    // - the x/y-length list must end with one of the 2-length cycle (distinct).
    // - there can be multiple 2-length cycles in the middle.
    //
    // NOTE:
    // Notice that each node can only be part of a single cycle, given that
    // it has only one outgoing edge.
    //
    // Topological sort allows for cycle detection, but we need more
    // information, i.e., length of cycles, where there could be multiple.
    // How to find all the cycles?
    //
    // i.e., Kahn's, if indegree[i] > 0?
    // favorite = [1, 0, 3, 2, 5, 4], three cycles of length 2
    // indegree = [1, 1, 1, 1, 1, 1].
    // max = 6, all 2-length cycles can be placed beside each other.
    //
    // vs.
    // favorite = [1, 2, 0, 4, 5, 3], two cycles of length 3
    // indegree = [1, 1, 1, 1, 1, 1].
    // max = 3, 3-length cycle, nothing outside.
    //
    // Kahn's can only help us identify nodes not in any cycle.
    // Not sufficient yet, but a good start.
    //
    // For nodes in a cycle, we need some way to track the lengths of any
    // acyclic list ending at the nodes in cycle.
    // A depth list would suffice.
    // The 2-length cycles are the trickiest parts. Need some visualizations,
    // but the left length and right length can be arbitrarily combined...
    const int n = favorite.size();

    std::vector<int> indegree(n, 0);
    for (int i = 0; i < n; ++i) {
      ++indegree[favorite[i]];
    }

    std::queue<int> frontier;
    for (int i = 0; i < n; ++i) {
      if (indegree[i] == 0) {
        frontier.push(i);
      }
    }

    // Topo sort to determine length of acyclic lists, and any connection
    // between the acyclic lists and cycles.
    // This is because 2-length cycles can be arbitrarily linked.
    std::vector<int> depth(n, 1);
    while (!frontier.empty()) {
      int curr = frontier.front();
      frontier.pop();

      int next = favorite[curr];
      depth[next] = std::max(depth[next], depth[curr] + 1);
      if (--indegree[next] == 0) {
        frontier.push(next);
      }
    }

    // DFS on any unprocessed nodes: i.e., indegree > 0.
    // Determine cycle length.
    int longestCycle = 0;
    int twoLengthCycle = 0;
    for (int start = 0; start < n; ++start) {
      if (indegree[start] == 0) {
        continue;
      }

      int cycleLength = 0;
      int iter = start;
      while (indegree[iter] > 0) {
        indegree[iter] = 0;
        ++cycleLength;
        iter = favorite[iter];
      }

      // two cases: cycle length > 2, or == 2.
      if (cycleLength > 2) {
        longestCycle = std::max(longestCycle, cycleLength);
      } else {
        // For 2-length, can be arbitrarily combined with other 2-lengths.
        // Must also take into account acyclic lists ending with the 2-length
        // cycle...
        // ARBITRARILY COMBINED
        twoLengthCycle += depth[start] + depth[favorite[start]];
      }
    }
    return std::max(longestCycle, twoLengthCycle);
  }
};
