#include <algorithm>
#include <array>
#include <queue>
#include <string>
#include <vector>

constexpr size_t ALPHABETS = 26;

class Solution {
 public:
  // Topological Sort / Kahn's Algorithm:
  // 1. Create adjacency graph/matrix containing the directed edges.
  //    A node B is dependent on A iff there is a directed edge from A to B.
  // 2. Enqueue all nodes with 0 incoming edges.
  // 3. For each of these nodes, add them to the sorted list, update their
  //    neighbour's indegree, and enqueue the neighbour if it has 0 indegree.
  // 4. Repeat 2 to 4 until the queue is empty.
  // 5. If the size of the sorted list is not equal to the number of nodes,
  //    then there is a circular dependency. Otherwise, return the list.
  std::string alienOrder(std::vector<std::string>& words) {
    // Given the sorted (with an unknown comparator) list of words, return a
    // order of the languages.

    // Used for cycle detection.
    std::array<bool, ALPHABETS> seen{};

    // Create dependency graph and calculate in-degree
    std::array<std::array<bool, ALPHABETS>, ALPHABETS> adj{{}};
    std::array<int, ALPHABETS> indegree{};

    for (int i = 0; i < words.size(); ++i) {
      for (char c : words[i]) {
        seen[c - 'a'] = true;
      }

      if (i > 0) {
        std::string_view prev = words[i - 1];
        std::string_view curr = words[i];

        int minLen = std::min(prev.length(), curr.length());

        // A little long, but basically, if the prev word is longer than the
        // current word, but the prefixes are the same, then an impossible
        // dependency is detected.
        if (prev.length() > curr.length() &&
            prev.substr(0, minLen) == curr.substr(0, minLen)) {
          return "";
        }

        for (int j = 0; j < minLen; ++j) {
          if (prev[j] != curr[j]) {
            // From the first difference in characters, add an edge from the
            // prev word to the curr word
            int from = prev[j] - 'a';
            int to = curr[j] - 'a';

            if (!adj[from][to]) {
              adj[from][to] = true;
              ++indegree[to];
            }
            // No need to look further
            break;
          }
        }
      }
    }

    std::queue<int> frontier;
    for (int i = 0; i < ALPHABETS; ++i) {
      if (seen[i] && indegree[i] == 0) {
        frontier.push(i);
      }
    }

    std::string sorted;
    sorted.reserve(ALPHABETS);
    while (!frontier.empty()) {
      int curr = frontier.front();
      frontier.pop();

      sorted += static_cast<char>('a' + curr);

      for (int neighbour = 0; neighbour < ALPHABETS; ++neighbour) {
        if (adj[curr][neighbour] && --indegree[neighbour] == 0) {
          frontier.push(neighbour);
        }
      }
    }

    int unique = std::count(seen.begin(), seen.end(), true);
    if (sorted.length() != unique) {
      return "";
    }
    return sorted;
  }
};
